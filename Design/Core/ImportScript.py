import sys
import os

def find_scripts_folder(start_path):
    current_path = start_path
    while True:
        scripts_path = os.path.join(current_path, 'scripts')
        if os.path.isdir(scripts_path):
            return scripts_path
        parent_path = os.path.dirname(current_path)
        if parent_path == current_path:
            raise FileNotFoundError("scripts folder not found")
        current_path = parent_path

# Get the directory of the current script
script_dir = os.path.dirname(os.path.realpath(__file__))

# Find the scripts folder
scripts_folder = find_scripts_folder(script_dir)

# Add the scripts folder to sys.path
sys.path.append(scripts_folder)