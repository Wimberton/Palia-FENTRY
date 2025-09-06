# 📚 Git Workflow for Branching and Merging

### Step 1: Pull the latest changes from `main`

Before making any changes, make sure your **main** branch is up to date:

```bash
git checkout main
git pull origin main
```

---

### Step 2: Merge `main` into your feature branch

Switch to your feature branch and merge the latest changes from **main**:

```bash
git checkout <feature/your-branch>
git merge main
```

This step keeps your feature branch updated with the latest code and minimizes conflicts when merging back into **main**.

---

### Step 3: Resolve any conflicts (if needed) and commit

If Git detects conflicts during the merge, manually resolve them in your code. Once resolved:

1. Stage the resolved changes:

   ```bash
   git add .
   ```

2. Commit the merge:
   ```bash
   git commit -m "Merged main into <your-feature-branch>"
   ```

---

### Step 4: Continue working and push your changes

Once the merge is complete, you can continue developing on your feature branch and push your changes to the remote repository:

```bash
git push origin <feature/your-branch>
```

> **Tip:** Do this regularly to avoid large merge conflicts later!

---

## ✅ **Merging Your Feature Branch Safely into Main**

### Step 1: Switch to the `main` branch

```bash
git checkout main
```

### Step 2: Pull the latest changes

```bash
git pull origin main
```

### Step 3: Merge your feature branch into `main`

```bash
git merge <your-feature-branch>
```

### Step 4: Push the updated `main` branch

```bash
git push origin main
```

> 🎉 **Congratulations!** Your feature branch is now part of the main codebase.

---

## 🔄 **General Workflow Summary**

1. Keep your **main** branch updated daily:

   ```bash
   git checkout main
   git pull origin main
   ```

2. Merge **main** into your feature branch frequently:

   ```bash
   git checkout <feature/your-branch>
   git merge main
   git push origin <feature/your-branch>
   ```

3. Safely merge your feature branch into **main** when ready:
   ```bash
   git checkout main
   git merge <your-feature-branch>
   git push origin main
   ```

---

By following this, you will maintain clean branches, avoid large conflicts, and smoothly merge changes back into the **main** branch.
