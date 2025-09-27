# Web Browser Project

A lightweight multi-tab web browser built with **C++** and **Qt Creator**. The project demonstrates the use of **Qt WebEngine** for rendering modern web content and covers essential browser functionality such as navigation, tab management, and URL handling.

## Features

- Multi-tab browsing with closable tabs
- Back, forward, and reload navigation controls
- URL bar with real-time updates
- Automatic tab renaming based on page titles
- Basic pop-up blocking
- Support for JavaScript, HTML/CSS, and WebGL

## Technologies

- C++ (C++17)
- Qt Creator
- Qt Widgets and Qt WebEngine
- Networking APIs and RESTful API integration

## Build Instructions

```bash
git clone https://github.com/yourusername/web-browser.git
cd web-browser
mkdir build && cd build
cmake ..
cmake --build .
./Web     # or Web.exe on Windows
```

## Future Work

- Bookmarks and favorites
- Persistent browsing history
- Theming and dark mode
- Stronger security and ad blocking
