import os
import re
import matplotlib.pyplot as plt

DATA_DIR = "./build/output/"
OUTPUT_DIR = "../plots/"

GRAPH_FAMILIES = ["Random4-C", "Random4-n", "Long-n", "Square-n", "Long-C", "Square-C", "USA-road-t"]

ALGORITHMS = ["Dijkstra", "Dial", "Radixheap"]

USA_REGIONS_ORDER = ["NY", "BAY", "COL", "FLA", "NW", "NE", "CAL", "LKS", "E", "W", "CTR"]

def parse_filename(filename):
    """Extract the graph family, algorithm, and X value from a filename."""
    match = re.match(r"(\w+)_([\w-]+)\.(\d+)\.0\.ss\.res", filename)
    if match:
        algorithm, family, x_value = match.groups()
        return algorithm, family, int(x_value)
    
    match = re.match(r"(\w+)_USA-road-t\.(\w+)\.ss\.res", filename)
    if match:
        algorithm, region = match.groups()
        family = "USA-road-t"
        x_value = region
        return algorithm, family, x_value
    
    print(f"Filename did not match pattern: {filename}")
    return None, None, None

def extract_value(filepath):
    """Extract the value from the first line of the file."""
    try:
        with open(filepath, 'r') as file:
            line = file.readline()
            match = re.match(r"t\s+([\d.eE+-]+)", line)
            if match:
                return float(match.group(1)) / 1000.0
    except Exception as e:
        print(f"Error reading {filepath}: {e}")
    return None

def group_files_by_family(data_dir):
    """Group files by graph family and algorithm."""
    files_by_family = {family: {algo: [] for algo in ALGORITHMS} for family in GRAPH_FAMILIES}

    for filename in os.listdir(data_dir):
        if filename.endswith(".p2p.res") or not filename.endswith(".ss.res"):
            continue
        filepath = os.path.join(data_dir, filename)
        algo, family, x_value = parse_filename(filename)
        if algo in ALGORITHMS and family in GRAPH_FAMILIES:
            files_by_family[family][algo].append((x_value, filepath))
    
    for family in files_by_family:
        for algo in files_by_family[family]:
            files_by_family[family][algo].sort(key=lambda x: x[0])
    
    return files_by_family

def plot_family_data(files_by_family, output_dir):
    """Generate and save plots for each graph family."""
    os.makedirs(output_dir, exist_ok=True)

    for family, algo_data in files_by_family.items():
        plt.figure(figsize=(10, 6))
        for algo, files in algo_data.items():
            x_values, y_values = [], []
            for x_value, filepath in files:
                t_value = extract_value(filepath)
                if t_value is not None:
                    x_values.append(x_value)
                    y_values.append(t_value)
            if family == "USA-road-t":
                x_value_to_y_value = {x_values[i] : y_values[i] for i in range(len(x_values))}
                x_values = USA_REGIONS_ORDER
                y_values = [x_value_to_y_value[x] for x in x_values]
                x_label = "Region"
            else:
                x_label = "Family size"
            plt.plot(x_values, y_values, marker="o", label=algo)
        
        plt.xlabel(x_label)
        plt.ylabel("Time (s)")
        plt.legend()
        plt.grid(True)
        plt.savefig(os.path.join(output_dir, f"{family}.png"))
        plt.close()

def main():
    files_by_family = group_files_by_family(DATA_DIR)
    plot_family_data(files_by_family, OUTPUT_DIR)

if __name__ == "__main__":
    main()
