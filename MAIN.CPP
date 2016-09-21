#include "LIST.CPP"
#include "STRING.H"

void copy_string(String &s, String t)
{
   s = t;
}
void write(String &s)
/* 
 
Post: The String parameter s is written to cout.
 
*/
{
   cout << s.c_str() << endl;
}
void main()
{
   String s, t("second string "), u = t;
   char * junk2;

   cout << s.c_str() << " " << t.c_str() << " " << u.c_str() << endl;

   write(s);
   write(t);
   write(u);
   cout << "\n";

   s = u;
   copy_string(t, s);

   write(s);
   write(t);
   write(u);
   cout << "\n";

   cout << strlen(s.c_str()) << "\n";
   const char *junk = s.c_str();
   cout << junk << "\n";
   junk2 = "first string";
   s = junk2;
   write(s);
   write(t);
   write(u);
   cout << "\n";
}
