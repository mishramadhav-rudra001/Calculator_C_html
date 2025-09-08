#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void html_head() {
    printf("Content-Type: text/html\n\n");
    printf("<!DOCTYPE html><html><head><meta charset='utf-8'><title>Result</title>"
           "<meta name='viewport' content='width=device-width,initial-scale=1'>"
           "<style>body{background:#0e0f12;color:#e5e7eb;font-family:Segoe UI,Arial;"
           "display:grid;place-items:center;height:100vh;margin:0}"
           ".card{background:#17181c;border-radius:14px;padding:24px 28px;"
           "box-shadow:0 10px 25px rgba(0,0,0,.35);text-align:center;min-width:280px}"
           ".n{font-variant-numeric:tabular-nums;font-size:28px}"
           "a{display:inline-block;margin-top:14px;padding:10px 16px;border-radius:10px;"
           "text-decoration:none;background:#2dd4bf;color:#0b0c10;font-weight:700}"
           "</style></head><body><div class='card'>");
}

static void html_tail() {
    printf("<a href='/calculator.html'>Back</a></div></body></html>");
}

int main(void) {
    html_head();

    char *q = getenv("QUERY_STRING");
    if (!q) { printf("<p>No input.</p>"); html_tail(); return 0; }

    // Simple parsing: a=<num>&b=<num>&op=<str>
    // NOTE: for robust parsing you'd split by & and decode, but OK for demo.
    double a = 0, b = 0;
    char op[8] = {0};
    // crude parse: this expects order a=...&b=...&op=...
    // Better to tokenize, but keeping minimal.
    if (sscanf(q, "a=%lf&b=%lf&op=%7s", &a, &b, op) < 3) {
        printf("<p>Bad query: %s</p>", q);
        html_tail(); return 0;
    }

    double out = 0;
    int ok = 1;

    if      (strcmp(op,"add")==0) out = a + b;
    else if (strcmp(op,"sub")==0) out = a - b;
    else if (strcmp(op,"mul")==0) out = a * b;
    else if (strcmp(op,"div")==0) {
        if (b==0) { printf("<p>Cannot divide by zero.</p>"); ok=0; }
        else out = a / b;
    } else {
        printf("<p>Unknown op: %s</p>", op); ok=0;
    }

    if (ok) {
        printf("<div class='n'>Result: %.12g</div>", out);
    }

    html_tail();
    return 0;
}
