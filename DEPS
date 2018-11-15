deps = {
  "src/third_party/libapps":
    "https://chromium.googlesource.com/apps/libapps.git@a13cbbf",
  "src/third_party/zip.js":
    "https://github.com/gildas-lormeau/zip.js.git@4c93974",
  "src/third_party/clang_tools":
    "https://chromium.googlesource.com/chromium/src/tools/clang.git@7aa7166",
}

deps_os = {
  "win": {
    "src/third_party/cygwin":
      "https://chromium.googlesource.com/chromium/deps/cygwin.git@4fbd5b9",
  },
}

hooks = [
  {
    "name": "clean_pyc",
    "pattern": ".",
    "action": [
        "python", "src/build_tools/clean_pyc.py", "src/build_tools", "src/lib"
    ],
  },
  {
    "name": "pip_install",
    "pattern": ".",
    "action": [
        "src/build_tools/pip_install.sh"
    ],
  },
]
