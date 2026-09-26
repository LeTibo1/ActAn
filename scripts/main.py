import sys
import traceback
import parser as ps
import data_extractor as de
import area_picker as ap
import plot_generator as pg

def main():
    args = ps.parse_args()
    
    # 1. extraction
    file = "activitétotale3.csv"
    if file:
        dts, data = de.run_extraction(file)

    # 2. pick area
    if data:
        data_area = ap.run_area_pick(dts, data)

    # 3. Plot both plots and calculate velocity
    if data_area:
        v = pg.run_plot_generation(file, data, data_area)
        print("v = ", v)

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(f"Error found: {e}", file=sys.stderr)
        traceback.print_exc()
        sys.exit(1)
