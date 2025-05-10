#include <stdio.h>
#include "mongoose.h"

static const char *s_http_addr = "http://localhost:8080";


static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        
        if (mg_http_match_uri(hm, "/")) {
            
            mg_http_reply(c, 200,
                "Content-Type: text/html\r\n",
                "<!DOCTYPE html><html><head><title>Конструктор</title></head><body>"
                "<h1>Создать поздравление</h1>"
                "<form method='POST' action='/submit'>"
                "<label>Имя: <input name='name' required></label><br>"
                "<label>Повод: <select name='occasion'>"
                "<option value='День рождения'>День рождения</option>"
                "<option value='Новый год'>Новый год</option>"
                "<option value='Выпускной'>Выпускной</option>"
                "</select></label><br>"
                "<button>Поздравить</button></form></body></html>");
        }
        else if (mg_http_match_uri(hm, "/submit")) {
            
            char name[50] = "", occasion[50] = "";
            mg_http_get_var(&hm->body, "name", name, sizeof(name));
            mg_http_get_var(&hm->body, "occasion", occasion, sizeof(occasion));
            
            
            mg_http_reply(c, 200,
                "Content-Type: text/html\r\n",
                "<!DOCTYPE html><html><head><title>Поздравление</title></head><body>"
                "<h1>Поздравление для %s</h1>"
                "<p>С %s!</p><p>Всего наилучшего!</p>"
                "<a href='/'>Назад</a></body></html>",
                name, occasion);
        }
        else {
            mg_http_reply(c, 404, NULL, "Not found");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    
    // Правильный вызов mg_http_listen с полным URL
    mg_http_listen(&mgr, s_http_addr, fn, NULL);
    
    printf("Server running on %s\n", s_http_addr);
    while (true) mg_mgr_poll(&mgr, 1000);
    
    mg_mgr_free(&mgr);
    return 0;
}
