#!/bin/bash

# emrun --browser firefox --port 8080 --serve_root .build_emscripten//src/platform/emscripten/ .build_emscripten//src/platform/emscripten/
# emrun --browser chrome --port 8080 --serve_root .build_emscripten//src/platform/emscripten/ .build_emscripten//src/platform/emscripten/
# emrun --browser chrome --port 8080 --serve_root / .build_emscripten//src/platform/emscripten/  --args --disable-web-security
# emrun --browser chrome --port 8080 --serve_root .build_emscripten//src/platform/emscripten/ .build_emscripten//src/platform/emscripten/  --args --disable-web-security
emrun --browser chrome .build_emscripten/src/platform/emscripten/

