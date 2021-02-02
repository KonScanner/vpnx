#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <regex>
#include <stdio.h>

using namespace std;

static inline string exec(const char *cmd)
{
  array<char, 128> buffer;
  string result;
  unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe)
  {
    throw runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
  {
    result += buffer.data();
  }
  return result;
}

static inline string regSearchnStore(string str1, string str2)
{
  smatch match; // store the text that matches the pattern here
  regex_search(str1, match, regex{str2, regex_constants::icase});
  // cout << "Matched text: " << match.str() << "\n"; // in case user wants to print
  return match.str();
}

int main(int argc, char *argv[])
{

  // if provided argument
  if (argc == 2)
  {
    string id = (string)argv[1];
    string match = regSearchnStore(exec("nmcli"), id);
    // if VPN network of name id exists in your system and is online
    if (match == id)
    {
      cout << id.c_str();
      string arg = "nmcli con down ";                                   // turn off vpn *
      string arg2 = "gsettings set org.gnome.system.proxy mode 'none'"; // turn off proxy **
      arg += id;                                                        // *
      const char *a = arg.c_str();
      const char *a2 = arg2.c_str(); // **
      exec(a);
      exec(a2);
      cout << "\nDisconnected from " << id << endl;
    }
    // if VPN network of name exists in your system and is offline
    else
    {
      cout << id.c_str();
      string arg = "nmcli con up ";                                       // turn on vpn *
      string arg2 = "gsettings set org.gnome.system.proxy mode 'manual'"; // turn on proxy **
      arg += id;                                                          // *
      const char *a = arg.c_str();
      const char *a2 = arg2.c_str(); // **
      exec(a);
      exec(a2);
      cout << "\nConnected to " << id << endl;
    }
  }
  // no provided arguments
  else
  {
    fprintf(stderr, "Usage: %s id<string>\n", argv[0]);
    return 1;
  }
  return 0;
}
