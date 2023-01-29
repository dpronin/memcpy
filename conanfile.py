# how to use semver https://devhints.io/semver

from conans import ConanFile, CMake, tools

class Mtfind(ConanFile):
    name = "memcpy"
    version = "0.1.0"
    author = "Denis Pronin"
    url = "https://github.com/dpronin/memcpy"
    description = "A compairing tool for memcpy"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_find_package"

    scm = {
        "type": "git",
        "subfolder": name,
        "url": "auto",
        "revision": "auto",
        "username": "git"
    }

    def build_requirements(self):
        self.build_requires("benchmark/[~1.7]")

    def _configure(self, verbose = True):
        cmake = CMake(self)
        cmake.verbose = verbose
        cmake.definitions['CMAKE_BUILD_TYPE'] = "Debug" if self.settings.build_type == "Debug" else "Release"
        cmake.configure(source_folder = self.name)
        return cmake

    def build(self):
        cmake = self._configure()
        cmake.build()
        cmake.test(output_on_failure = True)

    def package(self):
        cmake = self._configure()
        cmake.install()
