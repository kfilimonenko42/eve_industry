# eve industry

This project can help you get information about materials, prices, and production stages (eve online)

## Building

### Windows

```cmake
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

### Linux

```cmake
mkdir release
cd release
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . 
```

## Used third-party tools
- [**wxwidgets**](https://github.com/wxWidgets/wxWidgets)
- [**boost beast**](https://github.com/boostorg/boost)
- [**openssl**](https://github.com/openssl/openssl)
- [**nlohmann/json**](https://github.com/nlohmann/json)


## How to use

Create a new project\
![1](docs/examples/example_01.png)\
![2](docs/examples/example_02.png)

Enter types (format: "'type' 'count'") you want to produce (or copy from the game client)\
![3](docs/examples/example_03.png)\
![4](docs/examples/example_04.png)

Add stock (same ^^)\
![5](docs/examples/example_05.png)\
![6](docs/examples/example_06.png)

Configure blueprints settings (solar system/bp me/structure bonus/rig bonus/max runs per one job)\
![7](docs/examples/example_07.png)

Select solar system\
![8](docs/examples/example_08.png)

and press the calculate button\
![9](docs/examples/example_09.png)

All raw materials\
![10](docs/examples/example_10.png)

All materials from blueprints\
![11](docs/examples/example_11.png)

Stages\
![12](docs/examples/example_12.png)

## License

EVE industry is licensed under the GNU GPL v3.0, see LICENSE

## Contacts:

* EVE: Kirill Dif

## CCP Copyright Notice

© 2014 CCP hf. All rights reserved. "EVE", "EVE Online", "CCP", and all related logos and images are trademarks or registered trademarks of CCP hf.