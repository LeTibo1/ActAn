import sys
import parser as ps
import data_extractor as de
import area_picker as ap

def main():
    args = ps.parse_args()
    
    # 1. extraction
    file = "oxydase3.csv"
    if file:
        dts, data = de.run_extraction(file)

    # 2. pick area
    if data:
        data_area = ap.run_area_pick(dts, data)


if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(f"Error found: {e}", file=sys.stderr)
        sys.exit(1)
