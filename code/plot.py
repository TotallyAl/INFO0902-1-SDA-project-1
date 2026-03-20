import csv
import matplotlib.pyplot as plt
import os

# Fichiers CSV produits par benchmark.c
# Structure attendue : un CSV par (approche, dataset)
# Nommage : linear_25k.csv, sort_25k.csv, pq_25k.csv, etc.

DATASETS   = ["25k", "250k", "2500k"]
APPROACHES = {
    "linear": "Recherche linéaire",
    "sort":   "Tri + recherche binaire",
    "pq":     "File à priorité",
}
DATASET_LABELS = {
    "25k": "N = 25k",
    "250k": "N = 250k",
    "2500k": "N = 2500k",
}
COLORS = {
    "linear": "#E24B4A",
    "sort":   "#378ADD",
    "pq":     "#1D9E75",
}

DATASET_COLORS = {
    "25k": "#6A4C93",
    "250k": "#1982C4",
    "2500k": "#8AC926",
}

def load_csv(filepath):
    """Charge un CSV l,mean_time et retourne (ls, times)."""
    ls, times = [], []
    with open(filepath, newline="") as f:
        reader = csv.DictReader(f)
        for row in reader:
            ls.append(int(row["l"]))
            times.append(float(row["mean_time"]) * 1e6)  # conversion en µs
    return ls, times

for approach, approach_label in APPROACHES.items():
    fig, ax = plt.subplots(figsize=(8, 5))

    for dataset in DATASETS:
        filepath = f"{approach}_{dataset}.csv"
        if not os.path.exists(filepath):
            print(f"Fichier manquant : {filepath}")
            continue

        ls, times = load_csv(filepath)
        ax.plot(
            ls,
            times,
            marker="o",
            label=DATASET_LABELS[dataset],
            color=DATASET_COLORS[dataset],
            linewidth=1.8,
            markersize=4,
        )

    ax.set_title(f"{approach_label} (k = 20)", fontsize=13, fontweight="bold")
    ax.set_xlabel("Longueur de la requête l", fontsize=10)
    ax.set_ylabel("Temps moyen de acComplete (µs)", fontsize=10)
    ax.set_xticks(range(0, 11))
    ax.grid(True, linestyle="--", alpha=0.4)
    ax.legend(fontsize=9)

    fig.tight_layout()

    out_base = f"benchmark_{approach}"
    fig.savefig(f"{out_base}.pdf", bbox_inches="tight")
    fig.savefig(f"{out_base}.png", bbox_inches="tight", dpi=150)

print(
    "Graphes sauvegardés : "
    "benchmark_linear.(pdf/png), benchmark_sort.(pdf/png), benchmark_pq.(pdf/png)"
)
plt.show()
