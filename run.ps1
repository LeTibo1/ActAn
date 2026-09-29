Write-Host "Starting installation for ActAn on Windows..."

# compile project
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

if (\$LASTEXITCODE -ne 0) {
    Write-Host "Error: Compilation failed. Make sure CMake and Visual Studio/Build Tools are installed." -ForegroundColor Red
    Exit
}

# install python dependencies
Write-Host "Installing Python dependencies from requirements.txt..." -ForegroundColor Yellow
python -m pip install --upgrade pip --quiet
python -m pip install -r requirements.txt --quiet


# create PowerShell Profile if it does not exist yet
if (!(Test-Path \$PROFILE)) { 
    New-Item -Type File -Path \$PROFILE -Force | Out-Null
}

# Get current path to actan.exe
\$ExePath = Get-ChildItem -Path ".\build" -Filter "actan.exe" -Recurse | Select-Object -First 1 -ExpandProperty FullName

if (!\$ExePath) {
    Write-Host "Error: actan.exe not found in build directory." -ForegroundColor Red
    Exit
}

# check if function is already in profile, if not -> add it
\(ProfileContent = Get-Content\)PROFILE -ErrorAction SilentlyContinue
if (\$ProfileContent -notcontains "function actan") {
    \$FunctionString = "`nfunction actan { & '$ExePath' `\$args }"
    Add-Content \(PROFILE\)FunctionString
    Write-Host "Installation successful! Please restart your PowerShell window." -ForegroundColor Green
    Write-Host "You will then be able to use the 'actan' command from anywhere." -ForegroundColor Green
} else {
    Write-Host "ActAn function is already configured in your PowerShell profile." -ForegroundColor Yellow
}

