#ifndef CONSTANTS_H
#define CONSTANTS_H

#define TITLE "Greeting Card Generator"

#define FORM_HTML "<form method=\"POST\" action=\"/submit\">" \
"<label for=\"name\">Recipient Name:</label>" \
"<input type=\"text\" id=\"name\" name=\"name\" required><br><br>" \
"<label for=\"occasion\">Occasion:</label>" \
"<select id=\"occasion\" name=\"occasion\">" \
"<option value=\"Birthday\">Birthday</option>" \
"<option value=\"New Year\">New Year</option>" \
"<option value=\"Graduation\">Graduation</option>" \
"</select><br><br>" \
"<input type=\"submit\" value=\"Generate Greeting\">" \
"</form>"

#endif
