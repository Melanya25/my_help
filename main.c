#include <stdio.h>
#include "../lib/mongoose/mongoose.h"

// HTML шаблоны вынесены в отдельный заголовочный файл
#include "html_templates.h"

static const char *s_http_port = "8080";

// Новая сигнатура обработчика (без fn_data)
static void fn(struct mg_connection *c, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        
        if (mg_http_match_uri(hm, "/")) {
            mg_http_reply(c, 200, headers, form_html);
        }
        else if (mg_http_match_uri(hm, "/submit")) {
            char name[50], occasion[50];
            mg_http_get_var(&hm->body, "name", name, sizeof(name));
            mg_http_get_var(&hm->body, "occasion", occasion, sizeof(occasion));
            
            char response[1024];
            snprintf(response, sizeof(response), congrat_html, name, occasion);
            mg_http_reply(c, 200, headers, response);
        }
    }
}
