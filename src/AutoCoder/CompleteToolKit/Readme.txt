
1. if you dont already have venv Create python venv

python3 -m venv venv_autocoder

(Make sure it is ignored in repo)

2. Activate the venv

venv_autocoder\Scripts\activate

3. Install requirements

pip install -r requirements.txt

3. Make sure you have a valid QM statechart in XML

4. Create a list of events with time dispatched  > in.txt
EVENT 10
EVENT 15
EVENT 20

5. main.py XML\<yourStateChart.qm> in.txt