# ActAn

Makes life easier for you. It takes your .csv files and extract the values to obtain the desired graphs and velocities.

## Installation and Setup

Choose one of the options below to get the project files onto your computer.

### Step 1: Download the Project

#### Option A: Using the Terminal (Recommended)
If you have Git installed, open your terminal and run the following commands:
```bash
git clone https://github.com
cd ActAn
```

#### Option B: As a ZIP File (Without Git)
1. Click the green **"Code"** button at the top right of this GitHub page and select **"Download ZIP"**.
2. Extract the downloaded ZIP file on your computer.
3. Open your terminal and navigate into the extracted directory, for example:
```bash
cd ~/Downloads/ActAn-main
```

---

### Step 2: Compile the Program

Ensure you have `cmake` and a C++ compiler installed on your system (if not ask an ai ;)). Run these commands to build the application:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

---

### Step 3: Configure the Terminal Command

To run the tool from anywhere on your computer using the simple `actan` command, add a shortcut (alias) to your system profile.

#### For Linux:
```bash
echo "alias actan='\$(pwd)/actan.sh'" >> ~/.bashrc
source ~/.bashrc
```

#### For macOS:
```bash
echo "alias actan='\$(pwd)/actan.sh'" >> ~/.zshrc
source ~/.zshrc
```

#### For Windows (PowerShell):
Open your PowerShell and run the following commands to create a permanent alias:

```powershell
# 1. Create a PowerShell profile if it does not exist yet
if (!(Test-Path PROFILE)) New-Item -Type File -Path PROFILE -Force }

# 2. Add the actan shortcut to your profile
Add-Content \$PROFILE "function actan { & '\$((Get-Item .).FullName)\build\Debug\actan.exe' \$args }"
```

*Note for Windows:* Close and reopen your PowerShell window after running these commands to apply the changes. You can then run the tool from any folder by typing:
```cmd
actan
```


**Setup complete.** You can now open a new terminal window and run your program from any directory by typing:
```bash
actan
```

