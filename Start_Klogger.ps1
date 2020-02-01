$Default_proccess_name = ‘klaf’
$Default_logger_dir_name = ‘C:\temp’

$Proccess_name = Read-Host -Prompt "Input desired proccess name [default: '$Default_proccess_name']> "

if ([string]::IsNullOrWhiteSpace($Proccess_name)) {
    $Proccess_name = $Default_proccess_name
}

$Logger_dir_name = Read-Host -Prompt "Input desired directory to save the logger [default: '$Default_logger_dir_name']> "
if ([string]::IsNullOrWhiteSpace($Proccess_name)) {
    $Logger_dir_name = $Default_logger_dir_name
}

g++ ./main.cpp ./key_listener.cpp ./logger.cpp -std=c++14 -o $Proccess_name
Start-Process -FilePath .\$Proccess_name $Logger_dir_name -Wait -NoNewWindow
