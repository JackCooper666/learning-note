# install the conda by [`miniforge`](https://github.com/conda-forge/miniforge) installer.
go to the https://conda-forge.org/download/ to download the .sh file like Miniforge3-Linux-x86_64.sh

```bash
bash Miniforge3-Linux-x86_64.sh
```

then put this in your .bashrc file

```bash
# <<< mamba initialize <<<
echo "----------------------------------------"
echo "Do you want to initialize mamba? (y/n)"
read -r response
if [[ "$response" =~ ^([yY][eE][sS]|[yY])$ ]]; then
	export MAMBA_EXE='/home/zewen/miniforge3/bin/mamba';
	export MAMBA_ROOT_PREFIX='/home/zewen/miniforge3';
	__mamba_setup="$("$MAMBA_EXE" shell hook --shell bash --root-prefix "$MAMBA_ROOT_PREFIX" 2> /dev/null)"
	if [ $? -eq 0 ]; then
	    eval "$__mamba_setup"
	else
	    alias mamba="$MAMBA_EXE"  # Fallback on help from mamba activate
	fi
	unset __mamba_setup
	echo "mamba initialized."
else
	echo "Skipped mamba initialization."
fi
# <<< mamba initialize <<<
```
then `source ~/.bashrc` your bashrc, but if you activate conda now, the base conda env (base) will not activated automatically, so please run the following line to set the base as the default conda environment and activate automatically when you activate the conda, which is a clear way to check whether the conda is activated successfully
```bash
conda config --set auto_activate_base true
```
# install mamba
```bash
conda install mamba -c conda-forge
```
