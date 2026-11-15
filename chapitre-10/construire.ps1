# Compile chaque exercice en programme.exe, le lance avec entree.txt et compare la sortie
# au fichier de reference (attendu.txt pour les exos 1 a 7, resultat.txt pour les exos 8 a 10).
# Utilisation, depuis ce dossier :
#     powershell -ExecutionPolicy Bypass -File .\construire.ps1

$compilateur = $null
if (Get-Command clang++ -ErrorAction SilentlyContinue) { $compilateur = "clang++" }
elseif (Get-Command g++ -ErrorAction SilentlyContinue) { $compilateur = "g++" }
if (-not $compilateur) {
    Write-Host "Ni clang++ ni g++ n'est installe (ou ils ne sont pas dans le PATH)." -ForegroundColor Red
    exit 1
}
Write-Host "Compilateur : $compilateur"

foreach ($dossier in (Get-ChildItem -Directory -Path $PSScriptRoot | Sort-Object { [int]($_.Name -replace '^exo(\d+)-.*$', '$1') })) {
    $source = Get-ChildItem -Path $dossier.FullName -Filter *.cpp | Select-Object -First 1
    if (-not $source) { continue }

    $exe = Join-Path $dossier.FullName "programme.exe"
    & $compilateur -std=c++17 -Wall $source.FullName -o $exe
    if ($LASTEXITCODE -ne 0) {
        Write-Host ("ECHEC compilation : " + $dossier.Name) -ForegroundColor Red
        continue
    }

    $entree = Join-Path $dossier.FullName "entree.txt"
    $reference = Join-Path $dossier.FullName "attendu.txt"
    if (-not (Test-Path $reference)) { $reference = Join-Path $dossier.FullName "resultat.txt" }
    if (-not (Test-Path $entree) -or -not (Test-Path $reference)) {
        Write-Host ("Compile (rien a comparer) : " + $dossier.Name)
        continue
    }

    $sortie = Get-Content $entree | & $exe
    $ecarts = Compare-Object @($sortie) @(Get-Content $reference)
    if ($null -eq $ecarts) {
        Write-Host ("OK     " + $dossier.Name) -ForegroundColor Green
    } else {
        Write-Host ("DIFFERENT " + $dossier.Name) -ForegroundColor Yellow
        $ecarts | Format-Table | Out-String | Write-Host
    }
}
