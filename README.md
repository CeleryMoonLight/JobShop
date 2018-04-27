# Job Shop Scheduling Problem

## 开发指南

### 构建项目文件

若要生成 Visual Studio 对应的解决方案及项目文件，请遵循以下步骤：
- 至 [Download | CMake](https://cmake.org/download/) 下载 CMake 构建套件。对于 Windows 用户，可直接点击[这个链接](https://cmake.org/files/v3.10/cmake-3.10.3-win64-x64.msi)。
- **注意**：在安装过程中，务必选中 `Add CMake to the system PATH for the current user` 选项。
- 安装完毕后，请运行根目录下的 `./build.bat`。稍等后，可在 `./build/` 下找到 `JobShop.sln` 解决方案文件，打开即可启动 Visual Studio 进行开发工作。

### 编译与添加新的代码文件

- 右侧解决方案列表中，可看到三个项目：`ALL_BUILD`、`JobShop`、`ZERO_CHECK`。右键单击 `JobShop`，并选择设为启动项目。

- **注意**：若要添加新的源代码文件，**不要**在 Visual Studio 中直接添加。请先退出 Visual Studio，在 `./include/`（对于`.h`头文件）或 `./src/`（对于`.cpp`源文件）下手动新建文件，然后再运行 `./build.bat` 更新解决方案及项目文件，之后即可启动 Visual Studio 进行工作。