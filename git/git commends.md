# Get Start

1. Use the "git clone" or "git remote add" to git the remote repository

```git
git clone https://github.com/AAAAAAABYSSS/ME5413-Final-Project-Group6.git
```
or 
```git
git remote add upstream git@github.com:AAAAAAABYSSS/ME5413-Final-Project-Group6.git

git remote -v
```

2. Check your current branch
```git
git branch
```
3. load current branch to local
```git
git fetch
```
To fetch **all branches from both remotes**, including `biao` and `junqi` (which you expect to be in `upstream`), run:
```git
git fetch --all
```

4. Go to your own branch or create a new branch
```git
git checkout your/branch/path  // go to your branch 
```
```git
git checkout -b your/new/branch // create a new branch
```
5. commit your codes into the branch and store them a cloud buffer
```git
git add . // add all your local changes 
git add your/change/path // add one change
git commit -m "[your/branch] ..." // after add all changes
```
6. push the codes into github remote terminal
if you used `git remote` to connect with a github remote terminal
before you push, you should check the branch situations
```git
git remote -v
```
your branch may connected with multiple repositories. such like
```bash
~/zewen/fastlivo2-ac/src/FAST-LIVO2$ git remote -v 
origin https://github.com/hku-mars/FAST-LIVO2.git (fetch) 
origin https://github.com/hku-mars/FAST-LIVO2.git (push) 
upstream https://github.com/nuslde/DJBGS.git (fetch) 
upstream https://github.com/nuslde/DJBGS.git (push)
```

therefore, please determine which repository should is your destination to push
```git
git push --set-upstream origin zewen/fastlivo2-ac1
```
or
```git 
git push --set-upstream upstream zewen/fastlivo2-ac1
```

# How to pull thridparty submodule


# Pull Others' Repository -- this is wrong

1. check current branches
```git
git fetch
```
2. go to others' branches
```git
git checkout others/branches
```
3. pull
```git
git branch
git pull origin others/branches
git branch
```
4. go back to your branch
```git
git checkout your/branch
```
5. check current git status
```git
git branch
git status
```

# How to push submodules into your branches



## To restore your **previous pushed code** from your branch and overwrite the **current broken code**, follow these steps carefully:

---

### ✅ Step-by-step: Restore Previous Code from Remote Branch

Assuming:

- Your branch is called `your-branch-name`
    
- You already pushed working code yesterday
    

#### 1. **Discard all local changes and reset to remote**

⚠️ WARNING: This will delete all **uncommitted** and **local changes**.

```git
git fetch origin git reset --hard origin/your-branch-name
```
This means:

- `fetch`: Gets the latest snapshot from remote
    
- `reset --hard`: Resets your working directory, staging area, and branch to match the remote exactly
    

---

### 🛑 If You Only Want to Restore Specific Files

You can restore specific files instead of the whole project:
```git
git fetch origin git checkout origin/your-branch-name -- path/to/file.cpp
```


---

### 🧯 If You Want to Back Up the Broken Version First (Just in Case)

Before overwriting, you can back up your current state:

```git
git branch backup-broken-code
```


Now your broken version is saved in `backup-broken-code` in case you want to check it later.




