param (
    [string]$BuildType = "Debug",
    [string]$Compiler = "g++"
)

if (-not (Test-Path "build")) {
    New-Item -Path "build" -ItemType Directory | Out-Null
}
Set-Location -Path "build"

$cmake_cxx_compiler = "g++"
if ($Compiler -eq "clang") {
    $cmake_cxx_compiler = "clang++"
}

cmake .. "-DCMAKE_BUILD_TYPE=$BuildType" "-DCMAKE_CXX_COMPILER=$cmake_cxx_compiler"
cmake --build .
Set-Location -Path ".."
