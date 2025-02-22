🛠️ **Step-by-Step Guide to Using vcpkg for Your BakkesMod Plugin**
(Following the BakkesMod tutorial as closely as possible)

---

## **Step 1: Install vcpkg**
Follow the official Microsoft instructions here:  
🔗 [vcpkg Installation Guide](https://github.com/microsoft/vcpkg)

Or install vcpkg manually with these commands:

```cmd
# Clone vcpkg repository
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg

# Build vcpkg
bootstrap-vcpkg.bat
```

---

## **Step 2: Integrate vcpkg with Visual Studio**
Run the following command inside the `vcpkg` folder:

```cmd
vcpkg integrate install
```
This tells Visual Studio to use vcpkg automatically for dependencies.

---

## **Step 3: Define Dependencies**
Your **root folder** is where your `.sln` (solution file) is located. In your case, it is:

```
C:\MyFirstBakkesPlugin
```

This is the folder where you need to create the `vcpkg.json` file.

### **📌 Where to Place `vcpkg.json`**
- **Create `vcpkg.json` inside `C:\MyFirstBakkesPlugin`**, next to `MyFirstBakkesPlugin.sln`.
- It should **NOT** go inside `MyFirstBakkesPlugin/` or `build/`.

### **📌 Base `vcpkg.json` File**
Create a new file `vcpkg.json` with the following content:

```json
{
    "$schema": "https://raw.githubusercontent.com/microsoft/vcpkg-tool/main/docs/vcpkg.schema.json",
    "dependencies": []
}
```

### **Example `vcpkg.json` with Dependencies**
If you need libraries like `nlohmann-json`, `eventpp`, `websocketpp`, and `cpr`, modify `vcpkg.json` like this:

```json
{
    "$schema": "https://raw.githubusercontent.com/microsoft/vcpkg-tool/main/docs/vcpkg.schema.json",
    "dependencies": [
        "nlohmann-json",
        "eventpp",
        "websocketpp",
        "cpr"
    ]
}
```

🔗 [Find available vcpkg packages here](https://vcpkg.io/en/packages.html)

---

## **Step 4: Configure Visual Studio**
Now, open your plugin project in **Visual Studio** and do the following:

1. **Right-click on your project → Properties**
2. **Go to the new "vcpkg" section** (should appear if vcpkg was integrated correctly)
3. **Set "Use vcpkg Manifest" to Yes**
4. **Set "Use Static Libraries" to Yes**

✅ Done! Your project is now using vcpkg correctly.

---

## **Step 5: Add to `.gitignore` (Optional, but Recommended)**
To prevent unnecessary files from being pushed to Git, add this line to your `.gitignore` file:

```
vcpkg_installed/
```
This prevents compiled vcpkg libraries from being committed.

---

## **Step 6: Test Everything**
Now, **build your plugin in Visual Studio**.

💡 The first time you build, vcpkg will automatically download and compile the dependencies you listed in `vcpkg.json`. This may take some time.

---

## **🎯 TL;DR Summary**
✅ Install vcpkg  
✅ Integrate vcpkg with Visual Studio  
✅ Add `vcpkg.json` with dependencies  
✅ Set **Visual Studio** to **Use vcpkg Manifest** and **Use Static Libraries**  
✅ **Build your project!** 🚀  

---

## **❗ Important Notes**
- **Imgui** and **fmt** (used in BakkesMod) are **not required** in `vcpkg.json`. You can use the versions included in the BakkesMod SDK.
- If you ever need to add more dependencies, just update `vcpkg.json` and rebuild!

Now you’re fully set up with **vcpkg for your BakkesMod plugin!** 🎉

Let me know if you need help with anything! 🚀

