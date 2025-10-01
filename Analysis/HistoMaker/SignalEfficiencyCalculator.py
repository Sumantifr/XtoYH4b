import uproot
import awkward as ak
import ROOT

file = uproot.open("/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Analysis_NTuples/2023BPiX/SIGNAL/NoSelection//NMSSM_XtoYHto4B_MX-4000_MY-400_TuneCP5_13p6TeV_madgraph-pythia8.root")
tree = file["Tout"]

branches = [
    "nGenBPart",
    "GenBPart_pt",
    "GenBPart_eta",
    "GenBPart_phi",
    "GenBPart_mass",
    "GenBPart_pdgId",
    "GenBPart_mompdgId",
    "GenBPart_grmompdgId",
    "GenBPart_fromResonance"
]

data = tree.arrays(branches)

for i, nb in enumerate(data["nGenBPart"]):
    
    print(f"Event {i}: nGenBPart = {nb}")

    H_b1_index, H_b2_index, Y_b1_index, Y_b2_index = int(-1), int(-1), int(-1), int(-1)

    for j in range(nb):
        pt = data["GenBPart_pt"][i][j]
        eta = data["GenBPart_eta"][i][j]
        phi = data["GenBPart_phi"][i][j]
        mass = data["GenBPart_mass"][i][j]
        pdgId = data["GenBPart_pdgId"][i][j]
        mompdgId = data["GenBPart_mompdgId"][i][j]
        grmompdgId = data["GenBPart_grmompdgId"][i][j]
        fromRes = data["GenBPart_fromResonance"][i][j]

        # Get indices of b quarks and anti-quarks from H and Y

        if pdgId==5 and mompdgId==25:
            H_b1_index = j
        elif pdgId==-5 and mompdgId==25:
            H_b2_index = j
        elif pdgId==5 and mompdgId==35:
            Y_b1_index = j
        elif pdgId==-5 and mompdgId==35:
            Y_b2_index = j

        print(f"  GenBPart {j}: pt={pt}, eta={eta}, phi={phi}, mass={mass}, "
              f"pdgId={pdgId}, mompdgId={mompdgId}, grmompdgId={grmompdgId}, "
              f"fromResonance={fromRes}")

    print(f"Y_b1_index={Y_b1_index}, Y_b2_index={Y_b2_index}, H_b1_index={H_b1_index}, H_b2_index={H_b2_index}")

    # construct 4-momenta of b quarks and anti-quarks

    H_b1, H_b2, Y_b1, Y_b2 = ROOT.TLorentzVector(), ROOT.TLorentzVector(), ROOT.TLorentzVector(), ROOT.TLorentzVector()

    H_b1.SetPtEtaPhiM(data["GenBPart_pt"][i][H_b1_index], data["GenBPart_eta"][i][H_b1_index], data["GenBPart_phi"][i][H_b1_index], data["GenBPart_mass"][i][H_b1_index])
    H_b2.SetPtEtaPhiM(data["GenBPart_pt"][i][H_b2_index], data["GenBPart_eta"][i][H_b2_index], data["GenBPart_phi"][i][H_b2_index], data["GenBPart_mass"][i][H_b2_index])

    Y_b1.SetPtEtaPhiM(data["GenBPart_pt"][i][Y_b1_index], data["GenBPart_eta"][i][Y_b1_index], data["GenBPart_phi"][i][Y_b1_index], data["GenBPart_mass"][i][Y_b1_index])
    Y_b2.SetPtEtaPhiM(data["GenBPart_pt"][i][Y_b2_index], data["GenBPart_eta"][i][Y_b2_index], data["GenBPart_phi"][i][Y_b2_index], data["GenBPart_mass"][i][Y_b2_index])

    #angular distances

    dR_H_b1b2 = H_b1.DeltaR(H_b2)
    dR_Y_b1b2 = Y_b1.DeltaR(Y_b2)

    print(f"Y mass: {(Y_b1+Y_b2).M()}, H mass: {(H_b1+H_b2).M()}, dR_H_b1b2: {dR_H_b1b2}, dR_Y_b1b2: {dR_Y_b1b2}")

    print("-" * 50)
