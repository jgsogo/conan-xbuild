
import os
from conans import ConanFile, CMake

class testtool(ConanFile):
    name = "testtool"
    version = "0.1"
    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    exports = "*"

    generators = "cmake", "cmake_find_package"
    
    def requirements(self):
        self.requires("testlib/0.1@user/testing")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", keep_path=True)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("testtool_exe", src="bin", dst="bin", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["testtool"]
        self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))