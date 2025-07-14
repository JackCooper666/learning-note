# Install Anaconda on Ubuntu

The steps to install the Anaconda distribution on the Ubuntu system are explained in detail below:

## Step 1: Download Anaconda distribution

Visit the [official website](https://www.anaconda.com/download) of Anaconda distribution and download the latest version of Anaconda distribution installer for Ubuntu.![[conda_install_web.webp]]
## Step 2: Open the terminal

Open the terminal by pressing "Ctrl+Alt+T" or by clicking the terminal icon from the applications menu.![[terminal.webp]]

## Step 3: Navigate to downloads

Change the working directory of the terminal by executing the below command. You can also view the files in downloads using the 'ls' command. You can now see the Anaconda distribution installer in Downloads.
```bash
cd Dowloads
```
## Step 4: Run the installer

After changing the directory to Downloads, run the Anaconda installer by executing the following command.
```bash
bash Anaconda3-2024.02-1-Linux-x86_64.sh
```
## Step 5: Review the license agreement

Now, the Anaconda installer will ask the user to review the license agreement. Press "Enter" to review the license agreement.![[install_gui_1.webp]]

## Step 6: Accept license terms

After reading the license terms, the installer will ask whether you accept the license agreement. Type 'yes' and press 'Enter' to accept the agreement and continue the installation.![[install_gui_2.webp]]
## Step 7: Specify the installation location

After accepting the license agreement, the installer will ask for the installation folder for Anaconda distribution. You can press 'Enter' to install in the default location or you can specify your desired location. Then installer will start unpacking packages and install them. Installation may take some time.![[install_gui_3.webp]]
## Step 8: Initialize Anaconda

After installing Anaconda, the installer will ask the user to initialize the conda. You can type yes and press 'Enter' to initialize Anaconda and finish installation. It will add the 'conda' tool to the system path, so users can run it from any directory.![[install_gui_4.webp]]

## manually initialize the Conda when open terminal

open the bashrc
```bash
vim ~/.bashrc
```

put this inthe bashrc
```bash
echo "----------------------------------------"
echo "Do you want to initialize Conda? (y/n)"
read -r response
if [[ "$response" =~ ^([yY][eE][sS]|[yY])$ ]]; then
	__conda_setup="$('/home/arc/anaconda3/bin/conda' 'shell.bash' 'hook' 2> /dev/null)"
	if [ $? -eq 0 ]; then
		eval "$__conda_setup"
	else
		if [ -f "/home/arc/anaconda3/etc/profile.d/conda.sh" ]; then
			. "/home/arc/anaconda3/etc/profile.d/conda.sh"
		else
			export PATH="/home/arc/anaconda3/bin:$PATH"
		fi
	fi
	unset __conda_setup
	echo "Conda initialized. Use 'conda activate'."
else
	echo "Skipped Conda initialization. Run 'startconda' to enable it later."
fi
```

refresh your .bashrc
```bash
source ~/.bashrc
```

# uninstall
## Step 1: Execute the remove command

To uninstall Anaconda from your Ubuntu system, run the following command. It will remove all the files related to Anaconda.
```bash
rm -rf ~/anaconda3 ~/.condarc ~/.conda ~/.continuum
```
## Step 2: Open bashrc file

Now to remove Anaconda from the system path, open 'bashrc' on gedit using the following command.
```bash
gedit ~/.bashrc
```

## Step 3: Remove Anaconda from path

Scroll down to the end of the bashrc file and locate the contents related to the Anaconda installation. Select those parts and delete them to remove conda from the path.
```bash
echo "----------------------------------------"
echo "Do you want to initialize Conda? (y/n)"
read -r response
if [[ "$response" =~ ^([yY][eE][sS]|[yY])$ ]]; then
	__conda_setup="$('/home/arc/anaconda3/bin/conda' 'shell.bash' 'hook' 2> /dev/null)"
	if [ $? -eq 0 ]; then
		eval "$__conda_setup"
	else
		if [ -f "/home/arc/anaconda3/etc/profile.d/conda.sh" ]; then
			. "/home/arc/anaconda3/etc/profile.d/conda.sh"
		else
			export PATH="/home/arc/anaconda3/bin:$PATH"
		fi
	fi
	unset __conda_setup
	echo "Conda initialized. Use 'conda activate'."
else
	echo "Skipped Conda initialization. Run 'startconda' to enable it later."
fi
```

## Step 4: refresh your bashrc
```bash
source ~/.bashrc
```