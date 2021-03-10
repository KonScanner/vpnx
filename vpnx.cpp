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

static inline void proxy(bool connect)
{
  string arg2;
  if (connect == true)
  {
    arg2 = "gsettings set org.gnome.system.proxy mode 'manual'";
  }
  else
  {
    arg2 = "gsettings set org.gnome.system.proxy mode 'none'";
  }
  const char *a2 = arg2.c_str();
  exec(a2);
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
      string arg = "nmcli con down "; // turn off vpn *
      arg += id;                      // *
      const char *a = arg.c_str();
      exec(a);
      proxy(false);
      cout << "Changing to proxy=='none'." << endl;
      cout << "Disconnected from: " << id << endl;
    }

    // if VPN network of name exists in your system and is offline
    else
    {
      string arg = "nmcli con up "; // turn on vpn *
      arg += id;                    // *
      const char *a = arg.c_str();
      proxy(false); // ensuring setting is on off
      exec(a);
      proxy(true);
      cout << "Changing to proxy=='manual'." << endl;
      cout << "Connected to: " << id << endl;
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
