param (
    [string]$BuildType = "Debug",
    [string]$Compiler = "g++"
)

.\build.ps1 -BuildType $BuildType -Compiler $Compiler
if ($LASTEXITCODE -eq 0){
    .\build\bin\app.exe
}
