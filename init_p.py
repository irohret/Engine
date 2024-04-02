import os
import subprocess

def run_command(command):
    try:
        result = subprocess.run(command, shell=True, check=True, capture_output=True, text=True)
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        print(f"Error running command: {e.stderr}")
        return None

def initialize_submodules(repo_path):
    os.chdir(repo_path)
    print("Initializing submodules...")
    output = run_command("git submodule update --init --recursive")
    if output:
        print(output)

def update_submodules(repo_path):
    os.chdir(repo_path)
    print("Updating submodules...")
    output = run_command("git submodule foreach git pull origin main")
    if output:
        print(output)

def main():
    p = "C:\Users\Isaac\OneDrive\Desktop\github\Engine\CyberCore"
    repo_path = p
    initialize_submodules(repo_path)
    update_submodules(repo_path)

if __name__ == "__main__":
    main()