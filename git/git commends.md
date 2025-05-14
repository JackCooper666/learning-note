if # Get Start

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



# How to set a git link of a repository in your own project and push your cotents

### 🛠️ 1. **Initialize a Git repository locally**

Go to your project folder:

bash

复制编辑

`cd /path/to/your/project`

Initialize it as a Git repository:

bash

复制编辑

`git init`

---

### 📦 2. **Add your files and commit**

bash

复制编辑

`git add . git commit -m "Initial commit"`

---

### ☁️ 3. **Create a new GitHub repository**

Go to [https://github.com](https://github.com) → Click **"New repository"** → Fill in the name and other details → Click **"Create repository"**.

**Don’t initialize it with a README**, since you already did that locally.

---

### 🔗 4. **Connect your local repo to GitHub**

After creating the repo, GitHub will show you the remote URL like:

bash

复制编辑

`git remote add origin https://github.com/yourusername/your-repo-name.git`

Run that command in your terminal (replace the URL with your repo's URL).

---

### 🚀 5. **Push your code to GitHub**

bash

复制编辑

`git push -u origin master`

(If your default branch is `main`, use `main` instead of `master`.)

---

Let me know if you want to do this using GitHub Desktop, VS Code, or from a private repo — I can tweak the instructions.

4o


# git fetch
git fetch origin
Git will:

Connect to the remote (origin, usually GitHub)

Download all new branches, commits, and tags that you don’t have yet

Store them in your local .git database as origin/<branch-name>





 ### Stage All Deleted Files:

`git add -u`

This stages **modifications and deletions**, but **not untracked files** (i.e. new files).

---

### ✅ Or Stage a Specific Deletion:

`git rm src/jackal_navigation/CMakeLists.txt`

And if you want to remove the entire deleted folder (which Git already sees is gone):


`git rm -r src/jackal_navigation/`
