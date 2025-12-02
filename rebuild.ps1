param (
    [string]$BuildType = "Debug",
    [string]$Compiler = "g++"
)

Remove-Item -Path "build" -Recurse -Force -ErrorAction SilentlyContinue
.\build.ps1 -BuildType $BuildType -Compiler $Compiler
