import os
import subprocess
import sys

# Проекты и зависимости
projects = {
    "guess-number": ["numpy"],
    "bank-clients-analysis": ["pandas", "matplotlib", "seaborn", "jupyter"],
    "hh-resume-analysis": ["pandas", "numpy", "plotly", "scikit-learn"]
}

base_path = r"C:\Users\nulaa\Homework_SF"


def run(cmd, cwd):
    subprocess.run(cmd, cwd=cwd, check=True)


for project_name, packages in projects.items():
    project_path = os.path.join(base_path, project_name)

    if not os.path.exists(project_path):
        print(f"\n❌ {project_name} не найден")
        continue

    print(f"\n=== {project_name} ===")

    # 1. Создание виртуального окружения
    venv_path = os.path.join(project_path, ".venv")
    if not os.path.exists(venv_path):
        print("Создаю venv...")
        run([sys.executable, "-m", "venv", ".venv"], project_path)
    else:
        print("venv уже существует")

    # 2. Пути к python внутри venv
    if sys.platform == "win32":
        python_path = os.path.join(venv_path, "Scripts", "python")
    else:
        python_path = os.path.join(venv_path, "bin", "python")

    # 3. Обновление pip и установка pip-tools
    print("Обновляю pip и устанавливаю pip-tools...")
    run([python_path, "-m", "pip", "install", "--upgrade", "pip", "pip-tools"], project_path)

    # 4. Создание requirements.in
    req_in_path = os.path.join(project_path, "requirements.in")
    with open(req_in_path, "w") as f:
        f.write("\n".join(packages))

    # 5. Генерация requirements.txt через pip-tools
    print("Генерирую requirements.txt...")
    run([python_path, "-m", "piptools", "compile"], project_path)

    # 6. Создание .gitignore (если нет)
    gitignore_path = os.path.join(project_path, ".gitignore")
    if not os.path.exists(gitignore_path):
        with open(gitignore_path, "w") as f:
            f.write(
                "# Python\n"
                "__pycache__/\n"
                "*.py[cod]\n\n"
                "# Virtual env\n"
                ".venv/\n\n"
                "# IDE\n"
                ".vscode/\n"
                ".idea/\n\n"
                "# Logs\n"
                "*.log\n\n"
                "# Secrets\n"
                ".env\n"
            )
        print("Создан .gitignore")

    print(f"✅ {project_name} готов")

print("\n🎉 Все проекты настроены")