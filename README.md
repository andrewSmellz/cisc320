# Project Name

C++ / Qt 6 / SQLite desktop app.

## Requirements

- Windows 10/11
- [MSYS2](https://www.msys2.org/) installed at `C:\msys64` (default location)
- [VS Code](https://code.visualstudio.com/) with the **CMake Tools** and **C/C++** extensions

No Qt account or Qt online installer is needed. Qt comes from MSYS2.

> **Use UCRT64 only.** Do not install or use packages from the MINGW64, MSYS, or CLANG64 environments. Mixing runtimes causes missing/mismatched DLL errors.

## 1. Install the toolchain

Open the **MSYS2 UCRT64** shell from the Start menu (not "MSYS2 MSYS" or "MINGW64") and run:

```bash
pacman -Syu
```

If it asks you to close the terminal, close it, reopen **MSYS2 UCRT64**, and run `pacman -Syu` again.

Then install everything:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc \
          mingw-w64-ucrt-x86_64-cmake \
          mingw-w64-ucrt-x86_64-ninja \
          mingw-w64-ucrt-x86_64-qt6-base \
          mingw-w64-ucrt-x86_64-qt6-tools \
          mingw-w64-ucrt-x86_64-qt-creator
```

(`qt-creator` is optional if you only use VS Code.)

MSYS2 is rolling-release, so Qt versions can drift between teammates. If someone's build breaks after an update, everyone should run `pacman -Syu` and rebuild.

## 2. Add UCRT64 to your Windows PATH

This lets you build and run from PowerShell, cmd, or VS Code without opening the MSYS2 shell.

1. Start menu → search **"Edit environment variables for your account"**
2. Select **Path** → **Edit** → **New**
3. Add `C:\msys64\ucrt64\bin`
4. Move it **above** any other MinGW/gcc entries
5. Click OK on all dialogs
6. **Fully close and reopen VS Code** (and any terminals) so they pick up the new PATH

> **Do not** add `C:\msys64\usr\bin` to PATH. It shadows Windows tools and causes conflicts.

Verify in a new PowerShell window:

```powershell
g++ --version
cmake --version
ninja --version
```

All three should print versions. If any say "not recognized", the PATH entry is wrong or the terminal wasn't restarted.

## 3. Build and run

### Command line (PowerShell, cmd, or VS Code terminal)

```powershell
cmake -S . -B build -G Ninja
cmake --build build
.\build\<executable_name>.exe
```

Replace `<executable_name>` with the target defined in `CMakeLists.txt`.

### VS Code (CMake Tools)

1. Open the project folder in VS Code.
2. When prompted to select a kit, choose the **GCC** kit under `C:\msys64\ucrt64\bin`. If it isn't listed, run **CMake: Scan for Kits** from the command palette.
3. Press **F7** to build, then run from the CMake Tools status bar (play button) or the terminal.

The repo's `.vscode/settings.json` sets the Qt prefix so CMake can find Qt:

```json
{
  "cmake.configureArgs": ["-DCMAKE_PREFIX_PATH=C:/msys64/ucrt64"]
}
```

## Troubleshooting

| Problem | Fix |
|---|---|
| `Qt6 not found` in CMake | Make sure `-DCMAKE_PREFIX_PATH=C:/msys64/ucrt64` is set (see above), delete the `build/` folder, and reconfigure |
| Exe won't start / missing `Qt6*.dll` | `C:\msys64\ucrt64\bin` isn't on PATH, or the terminal wasn't restarted after adding it |
| Missing `libgcc` / `libstdc++` DLL errors | MINGW64 and UCRT64 got mixed. Remove any `C:\msys64\mingw64\bin` entry from PATH |
| `command not found` when pasting into MSYS2 | Invisible characters got pasted. Retype the first word or use right-click paste |
| VS Code can't find the compiler | Run **CMake: Scan for Kits** and pick the UCRT64 GCC kit |
| Stale build errors after switching kits | Delete `build/` and reconfigure |

## Sharing a standalone build

To give someone a build that runs without MSYS2 installed:

```powershell
windeployqt6 .\build\<executable_name>.exe
```

Zip the exe together with the DLLs and folders it copies next to it. Attach it to a GitHub Release. **Do not commit binaries to the repo.**

## Repo conventions

- Commit source, `.ui`, `.qrc`, and `CMakeLists.txt`. Do not commit `build/`, `*.user`, or `.db` files.
- Commit the SQL schema/seed scripts instead of database files.
- Use CMake only (no `.pro` files) so everyone can use their own editor.