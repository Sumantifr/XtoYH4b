source /data/dust/user/chatterj/environments/bdt/bin/activate

python3 Train_BDT_Pairing.py --usemassfraction 1 --fraction_low 0.0  --fraction_high 1.5 
python3 Train_BDT_Pairing.py --usemassfraction 1 --fraction_low 1.5  --fraction_high 2.5 
python3 Train_BDT_Pairing.py --usemassfraction 1 --fraction_low 2.5  --fraction_high 3.0 
python3 Train_BDT_Pairing.py --usemassfraction 1 --fraction_low 3.0  --fraction_high 100.0 
