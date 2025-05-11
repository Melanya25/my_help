#include <stdio.h>
#include <string.h>
#include "mongoose.h"

#define TEMPLATE_DIR "templates/"
#define STATIC_DIR "static/"

static const char *s_http_addr = "http://0.0.0.0:8080";

// Template rendering function
static void render_template(struct mg_connection *c, const char *filename, 
                          const char *vars[][2], size_t num_vars) {
    char path[256], content[4096];
    snprintf(path, sizeof(path), "%s%s", TEMPLATE_DIR, filename);
    
    FILE *fp = fopen(path, "rb");
    if (!fp) {
        mg_http_reply(c, 500, "Content-Type: text/plain\r\n", "Template not found");
        return;
    }

    size_t len = fread(content, 1, sizeof(content) - 1, fp);
    content[len] = '\0';
    fclose(fp);

    // Replace template variables
    for (size_t i = 0; i < num_vars; i++) {
        char placeholder[32];
        snprintf(placeholder, sizeof(placeholder), "{{%s}}", vars[i][0]);
        
        char *pos = strstr(content, placeholder);
        if (pos) {
            size_t plen = strlen(placeholder);
            size_t vlen = strlen(vars[i][1]);
            memmove(pos + vlen, pos + plen, strlen(pos + plen) + 1);
            memcpy(pos, vars[i][1], vlen);
        }
    }

    mg_http_reply(c, 200, 
                 "Content-Type: text/html\r\n"
                 "Cache-Control: no-cache\r\n",
                 "%s", content);
}

// Request handler
static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *)ev_data;

        // Serve static files
        if (mg_http_match_uri(hm, "/static/*")) {
            mg_http_serve_dir(c, hm, STATIC_DIR);
            return;
        }

        // Handle routes
        if (mg_http_match_uri(hm, "/")) {
            render_template(c, "form.html", NULL, 0);
        } 
        else if (mg_http_match_uri(hm, "/submit")) {
            char name[50] = "", occasion[50] = "";
            mg_http_get_var(&hm->body, "name", name, sizeof(name));
            mg_http_get_var(&hm->body, "occasion", occasion, sizeof(occasion));

            const char *vars[][2] = {
                {"name", name},
                {"occasion", occasion}
            };
            render_template(c, "congratulate.html", vars, 2);
        }
        else {
            render_template(c, "error.html", NULL, 0);
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);

    // Create HTTP server
    if (!mg_http_listen(&mgr, s_http_addr, fn, NULL)) {
        fprintf(stderr, "Failed to start server on %s\n", s_http_addr);
        return 1;
    }

    printf("Server running on %s\n", s_http_addr);
    
    // Event loop
    while (true) mg_mgr_poll(&mgr, 1000);
    
    mg_mgr_free(&mgr);
    return 0;
}
