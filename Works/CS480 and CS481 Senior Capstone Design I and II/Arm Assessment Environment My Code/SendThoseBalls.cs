using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class SendThoseBalls : MonoBehaviour
{
    public TaskConfig taskConfig;
    public GameObject homeBall, startBall, goalBall;
    public int taskRepeats = 2; // Edit 4/23
    public TMP_InputField input;    // Edit 4/24

    public Toggle toggleHome; // Alex Peña 4/26/22

    private float initHomeX, initHomeY, initHomeZ;
    private float initStartX, initStartY, initStartZ;
    private float initGoalX, initGoalY, initGoalZ;

    void Start()
    {
        initHomeX = homeBall.transform.position.x;
        initHomeY = homeBall.transform.position.y;
        initHomeZ = homeBall.transform.position.z;

        initStartX = startBall.transform.position.x;
        initStartY = startBall.transform.position.y;
        initStartZ = startBall.transform.position.z;

        initGoalX = goalBall.transform.position.x;
        initGoalY = goalBall.transform.position.y;
        initGoalZ = goalBall.transform.position.z;
    }

    public void SendItYeet()
    {
        var pConf = taskConfig.conf as PointToPointConfig;
        if (pConf == null)
            return;

        pConf.homeX = homeBall.transform.position.x - initHomeX;
        pConf.homeY = homeBall.transform.position.y - initHomeY;
        pConf.homeZ= homeBall.transform.position.z - initHomeZ;

        pConf.startX = startBall.transform.position.x - initStartX;
        pConf.startY = startBall.transform.position.y - initStartY;
        pConf.startZ = startBall.transform.position.z - initStartZ;

        pConf.goalX = goalBall.transform.position.x - initGoalX;
        pConf.goalY = goalBall.transform.position.y - initGoalY;
        pConf.goalZ = goalBall.transform.position.z - initGoalZ;

        // Edit 4/24 ---> This is forsaken, too much trouble was caused here (it works though)
        //string temp = input.GetComponent<TextMeshProUGUI>().text;
        //temp = temp.Replace("\\n", "");
        //("[" + temp + "]");
        //if (!string.IsNullOrEmpty(temp) && int.TryParse(temp, out int num))
        if (int.TryParse(input.text, out int num))
        {
            //print("You de winna");
            taskRepeats = num;
            pConf.runs = taskRepeats;    // Edit 4/23 // Alex Peña 4/25/22
        }
        // pConf.runs = taskRepeats;    // Edit 4/23 // Alex Peña 4/25/22

        pConf.useHome = toggleHome.isOn;
    }
}
