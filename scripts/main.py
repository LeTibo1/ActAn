import sys
import os
import traceback
import json
import parser as ps
import data_extractor as de
import area_picker as ap
import plot_generator as pg

def main():
    args = ps.parse_args()
    file = args.file
    results = {}
    
    # 1. extraction
    if file:
        dts, data = de.run_extraction(file)

    # 2. pick area
    if data:
        data_area = ap.run_area_pick(dts, data, args.area_no, args.tframe_run, args.thresh, args.is_dosage)

    # 3. Plot both plots and calculate velocity
    if data_area:
        v, slope = pg.run_plot_generation(file, data, data_area, args.epsilon, args.vol_cuvette, args.is_dosage)
        results["v"] = v
        results["slope"] = slope

        with open("temp_result.json", "w") as f:
            json.dump(results, f)

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(f"Error found: {e}", file=sys.stderr)
        traceback.print_exc()
        sys.exit(1)
