# terrain-generation

## Prérequis

Ce projet fonctionne avec CMake et Vcpkg il est donc nécessaire d'avoir les deux de préalablement installés.

Vous devez aussi avoir configuré les variables d'environnement suivantes:  
- `VCPKG_ROOT`: `votre/chemin/absolu/vers/vcpkg`
- `VCPKG_DEFAULT_TRIPLET`: `x64-windows` ou bien le format qui correspond à votre pc


## Submodules

### Windows

`git submodule update --init --recursive`

`.\vcpkg\bootstrap-vcpkg.bat`

`.\vcpkg\vcpkg.exe install --triplet x64-windows`

### Linux

`git submodule update --init --recursive`

`./vcpkg/bootstrap-vcpkg.sh`

`./vcpkg/vcpkg install --triplet x64-linux`

### Mac

`git submodule update --init --recursive`

`./vcpkg/bootstrap-vcpkg.sh`

`./vcpkg/vcpkg install --triplet x64-osx`