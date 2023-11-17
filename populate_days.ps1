#input paths
$sourceFile = "./main.cpp"
$destDir = "./src"

for ($day = 1; $day -le 25; $day++) {
    # Format day number with leading zero if needed
    $dayFormatted = "{0:D2}" -f $day
    
    # Create directory if it doesn't exist
    $directoryPath = Join-Path $destDir ("day" + $dayFormatted)
    if (-not (Test-Path -Path $directoryPath -PathType Container)) {
        New-Item -ItemType Directory -Path $directoryPath | Out-Null
    }

    #copy over the file
    $destinationFile = Join-Path $directoryPath ([System.IO.Path]::GetFileName($sourceFile))
    Copy-Item -Path $sourceFile -Destination $directoryPath -Force
}

Write-Host "Done."
