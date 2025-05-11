#include <stdio.h>
#include "mongoose.h"

static const char *s_http_addr = "http://0.0.0.0:8080";

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *)ev_data;
        
        if (mg_http_match_uri(hm, "/")) {
            mg_http_reply(c, 200, "Content-Type: text/html\r\n",
                "<!DOCTYPE html><html><head><title>Greeting Card Generator</title></head><body>"
                "<h1>Create Greeting Card</h1>"
                "<form method='POST' action='/submit'>"
                "<label>Recipient Name: <input name='name' required></label><br><br>"
                "<label>Occasion: <select name='occasion'>"
                "<option value='Birthday'>Birthday</option>"
                "<option value='New Year'>New Year</option>"
                "<option value='Graduation'>Graduation</option>"
                "</select></label><br><br>"
                "<input type='submit' value='Generate Greeting'>"
                "</form></body></html>");
        }
        else if (mg_http_match_uri(hm, "/submit")) {
            char name[50] = "", occasion[50] = "";
            mg_http_get_var(&hm->body, "name", name, sizeof(name));
            mg_http_get_var(&hm->body, "occasion", occasion, sizeof(occasion));
            
            mg_http_reply(c, 200, "Content-Type: text/html\r\n",
                "<!DOCTYPE html><html><head><title>Your Greeting Card</title></head><body>"
                "<h1>Greeting for %s</h1>"
                "<p>Congratulations on your %s!</p>"
                "<p>Wishing you all the best!</p>"
                "<a href='/'>Create another card</a></body></html>",
                name, occasion);
        }
        else {
            mg_http_reply(c, 404, NULL, "Page not found");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    
    if (!mg_http_listen(&mgr, s_http_addr, fn, NULL)) {
        printf("Failed to start server on %s\n", s_http_addr);
        return 1;
    }
    
    printf("Server running on %s\n", s_http_addr);
    while (true) mg_mgr_poll(&mgr, 1000);
    
    return 0;
}
