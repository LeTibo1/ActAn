# ActAn

Makes life easier for you. It takes your .csv files and extract the values to obtain the desired graphs and velocities.

## Installation and Setup

Choose one of the options below to get the project files onto your computer.

### Step 1: Download the Project

#### Option A: Using the Terminal (Recommended)
Navigate to the directory where you want to keep the project permanently (for example, your programs or development folder), then run:
```bash
git clone https://github.com/LeTibo1/ActAn
cd ActAn
```

#### Option B: As a ZIP File (Without Git)
1. Click the green **"Code"** button at the top right of this GitHub page and select **"Download ZIP"**.
2. Extract the downloaded ZIP file.
3. **Important:** Move the extracted folder to a permanent location where you can find it again (for example, your programs folder or a dedicated applications directory). Do not leave it in your Downloads folder.
4. Open your terminal or PowerShell, and navigate into that final directory:
```bash
cd /path/to/your/permanent/location/ActAn-main
```

---

### Step 2: Run the Automated Installation Script

Run the automated script matching your operating system. The script will automatically check for required tools (CMake, C++, and Python), install Python if it is missing, compile the project, and create a global terminal shortcut.

#### For Linux and macOS:
Run the following command in your terminal:
```bash
chmod +x run.sh && ./run.sh
```

#### For Windows:
Open PowerShell and run the following command:
```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; .\run.ps1
```

**Setup complete.** Restart your terminal or PowerShell window. You can now run your program from any directory by typing:
```text
actan
```
