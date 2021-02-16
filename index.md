# vpnx

## What is `vpnx`?

- An easy way for `gnome`-based distro users (Ubuntu, Pop-OS, etc.), to be able to activate their **vpn** and change their **proxy** settings using a simple terminal command, instead of having to go through a user interface.

## How does it work?

- By the user passing in the `vpn_id` configuration they want to connect to, `vpnx` looks to see if it's already active, if not it will create a connection as well as change the proxy settings from `off` to `manual` by default.

### Use case:

Connecting:

```bash
$ vpnx vpn_id
Connected to vpn_id
```

Disconnecting:

```bash
$ vpnx vpn_id
Disconnected from vpn_id
```

### Requirements:

- `nmcli`
- Proxy settings configured through gnome menu

#### Ideas for further versions:

- Have `stdout` to show connection process when connecting to **vpn**.
- Separate **vpn** connection with **proxy** activation, but having proxy activation set to `True` by default.

#### References:

- <a href="https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po"  > C++ `exec()` example</a>
