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





# token - free push/pull

如果你只想为 **这个单一仓库**（`https://github.com/JackCooper666/learning-note.git`）实现免密码 `git push/pull`，有两个简洁可选方案：

## ✅ 方法一（简单快速，不安全）：只为该仓库记住 token

适合个人开发机，操作简单。
### Step 1: 进入你的仓库目录
```git
cd ~/Documents/learning-note
```

### Step 2: 设置只对当前仓库记住密码（token）

```git
git config credential.helper store
```

### Step 3: 执行一次 `push` 或 `pull` 并输入 GitHub 用户名 + PAT（token）
```git
git pull
# 或者
git push
```

这时 Git 会要求你输入用户名和密码：
- 用户名：你的 GitHub 用户名
- 密码：GitHub 生成的 **Personal Access Token (PAT)**（不是你的 GitHub 密码）
Git 会将凭据保存在该仓库下的 `~/.git-credentials` 文件中，之后就不会再要求输入了。

