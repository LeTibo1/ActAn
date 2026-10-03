import argparse

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--file", type=str)
    parser.add_argument("--area_no", type=int)
    parser.add_argument("--tframe_run", type=int)
    parser.add_argument("--thresh", type=float)
    parser.add_argument("--epsilon", type=float)
    parser.add_argument("--vol_cuvette", type=float)
    parser.add_argument("--is_dosage", type=int)

    return parser.parse_args()
