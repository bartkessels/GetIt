# GetIt

Application to send HTTP requests to test API's.

## Screenshots

![GetIt Body](data/screenshots/body.png)
![GetIt Headers](data/screenshots/headers.png)
![GetIt Cookies](data/screenshots/cookies.png)
![GetIt Authentication](data/screenshots/authentication.png)
![GetIt Response](data/screenshots/response.png)

## What can I do with it?

You can send numerous requests to a webserver. If you need it there is an
option for authentication, right now only basic auth and digest auth.

## Required packages

### Building
- gtk3-devel
- python3-devel
- automake
- gettext
- intltool
- itstool
- desktop-file-utils
- libnotify-devel

### Installing
- gtk3
- pygobject3
- python3-requests
- python3-jsonpickle
- libnotify

## Features

- Add multiple form-data elements to the body
- Add custom data to the body
- Add files to a request
- Add cookies to a request
- Add multiple headers
- Use basic auth or digest auth
- Response data is displayed with syntax highlighting
- All headers from the response are shown
- Save a request
- Open a request

[GetIt features playlist](https://www.youtube.com/playlist?list=PLP-QZD6Cd0MWh7969cLZg31gO71s44Bk4)

## How to build
```
sudo mkdir -p /usr/share/getit/ui
sudo cp -r data/ui/* /usr/share/getit/ui

bash autogen.sh
./configure
sudo make install
```
And then run `./bin/getit`

If you don't copy the .ui files the application will crash because
it can't find the .ui files file.

## COPR

If you have Fedora and don't want to build GetIt from source you can easily install it using dnf copr.

```
sudo dnf copr enable bartkessels/getit
sudo dnf install getit
```
