param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$File,
    [string]$Output = ""
)

$Root = Split-Path -Parent $PSScriptRoot
$Compose = Join-Path $PSScriptRoot "docker-compose.yml"

$File = $File.Replace("\", "/").TrimStart("./")

if ($Output -eq "") {
    $Output = [System.IO.Path]::GetFileNameWithoutExtension($File)
}

Write-Host "Compilando $File ..."
docker compose -f $Compose exec cpp g++ -std=c++17 -Wall -g "$File" -o "$Output"
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}
Write-Host "Executando $Output ..."
docker compose -f $Compose exec cpp "./$Output"