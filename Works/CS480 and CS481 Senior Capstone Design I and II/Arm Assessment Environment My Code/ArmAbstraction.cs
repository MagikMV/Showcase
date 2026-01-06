using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Animations.Rigging;

public class ArmAbstraction : MonoBehaviour
{
    public GameObject rightRig, leftRig;
    public GameObject target1, target2;
    public GameObject rightArmMover, leftArmMover;
    public GameObject rightShoulder, leftShoulder;

    private RotateThatThang rUpper, rLower, rHand;  // Scripts For Right
    private RotateThatThang Upper, Lower, Hand;     // Scripts For Left
    private GameObject go_rUp, go_rLow, go_rHand;   // Right
    private GameObject go_Up, go_Low, go_Hand;      // Left
    private ShoulderControl rShoulderScript, ShoulderScript;

    private enum Part { up, low, hand}
    private Part part = Part.up;

    void Start()
    {
        go_rUp = rightRig.transform.Find("rUpperControl").gameObject;
        rUpper = go_rUp.GetComponent<RotateThatThang>();
        go_rLow = rightRig.transform.Find("rLowerControl").gameObject;
        rLower = go_rLow.GetComponent<RotateThatThang>();
        go_rHand = rightRig.transform.Find("rHandControl").gameObject;
        rHand = go_rHand.GetComponent<RotateThatThang>();

        go_Up = leftRig.transform.Find("UpperControl").gameObject;
        Upper = go_Up.GetComponent<RotateThatThang>();
        go_Low = leftRig.transform.Find("LowerControl").gameObject;
        Lower = go_Low.GetComponent<RotateThatThang>();
        go_Hand = leftRig.transform.Find("HandControl").gameObject;
        Hand = go_Hand.GetComponent<RotateThatThang>();

        rShoulderScript = rightShoulder.GetComponent<ShoulderControl>();
        ShoulderScript = leftShoulder.GetComponent<ShoulderControl>();
    }

    private void MatchRotation()
    {
        go_rUp.transform.localRotation = go_Up.transform.localRotation = Quaternion.identity;
        go_rLow.transform.localRotation = go_Low.transform.localRotation = Quaternion.identity;
        go_rHand.transform.localRotation = go_Hand.transform.localRotation = Quaternion.identity;

        rightShoulder.transform.localRotation = leftShoulder.transform.localRotation = Quaternion.identity;
    }

    private void PartInit(Part part)
    {
        if (part == Part.up)
        {
            rUpper.Init();
            Upper.Init();
        }
        else if (part == Part.low)
        {
            rLower.Init();
            Lower.Init();
        }
        else if (part == Part.hand)
        {
            rHand.Init();
            Hand.Init();
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Z))        // Left Arm Only
        {
            rightRig.SetActive(false);
            leftRig.SetActive(true);
            Upper.leftOnly = Lower.leftOnly = Hand.leftOnly = true;

            PartInit(part);
        }
        else if (Input.GetKeyDown(KeyCode.X))   // Both Arms
        {
            rightRig.SetActive(true);
            leftRig.SetActive(true);
            Upper.leftOnly = Lower.leftOnly = Hand.leftOnly = false;

            PartInit(part);

            // Code to match rotations, could have slicker code later
            MatchRotation();
        }
        else if (Input.GetKeyDown(KeyCode.C))   // Right Arm Only
        {
            rightRig.SetActive(true);
            leftRig.SetActive(false);
            Upper.leftOnly = Lower.leftOnly = Hand.leftOnly = false;

            PartInit(part);
        }


        if (Input.GetKeyDown(KeyCode.Alpha1))       // Upper
        {
            target1.GetComponent<FullControl>().ResetTarget();
            target1.GetComponent<FullControl>().enabled = false;
            target2.GetComponent<FullControl>().ResetTarget();
            target2.GetComponent<FullControl>().enabled = false;

            rShoulderScript.enabled = ShoulderScript.enabled = false;

            // Turn off the respective scripts
            rLower.enabled = Lower.enabled = false;
            rHand.enabled = Hand.enabled = false;
            rUpper.enabled = Upper.enabled = true;

            part = Part.up;
            PartInit(part);
        }
        else if (Input.GetKeyDown(KeyCode.Alpha2))  // Lower
        {
            target1.GetComponent<FullControl>().ResetTarget();
            target1.GetComponent<FullControl>().enabled = false;
            target2.GetComponent<FullControl>().ResetTarget();
            target2.GetComponent<FullControl>().enabled = false;

            rShoulderScript.enabled = ShoulderScript.enabled = false;

            // Turn off the respective scripts
            rUpper.enabled = Upper.enabled = false;
            rHand.enabled = Hand.enabled = false;
            rLower.enabled = Lower.enabled = true;

            part = Part.low;
            PartInit(part);
        }
        else if (Input.GetKeyDown(KeyCode.Alpha3))  // Hand
        {
            target1.GetComponent<FullControl>().ResetTarget();
            target1.GetComponent<FullControl>().enabled = false;
            target2.GetComponent<FullControl>().ResetTarget();
            target2.GetComponent<FullControl>().enabled = false;

            rShoulderScript.enabled = ShoulderScript.enabled = false;

            // Turn off the respective scripts
            rUpper.enabled = Upper.enabled = false;
            rLower.enabled = Lower.enabled = false;
            rHand.enabled = Hand.enabled = true;

            part = Part.hand;
            PartInit(part);
        }
        else if (Input.GetKeyDown(KeyCode.Alpha4))  // Full Right
        {
            target2.GetComponent<FullControl>().ResetTarget();
            target2.GetComponent<FullControl>().enabled = false;
            rUpper.enabled = Upper.enabled = false;
            rLower.enabled = Lower.enabled = false;
            rHand.enabled = Hand.enabled = false;
            target2.GetComponent<FullControl>().enabled = false;
            rShoulderScript.enabled = ShoulderScript.enabled = false;

            // Turn on
            target1.GetComponent<FullControl>().enabled = true;
        }
        else if (Input.GetKeyDown(KeyCode.Alpha5))  // Full Left
        {
            target1.GetComponent<FullControl>().ResetTarget();
            target1.GetComponent<FullControl>().enabled = false;
            rUpper.enabled = Upper.enabled = false;
            rLower.enabled = Lower.enabled = false;
            rHand.enabled = Hand.enabled = false;
            target1.GetComponent<FullControl>().enabled = false;
            rShoulderScript.enabled = ShoulderScript.enabled = false;

            // Turn on
            target2.GetComponent<FullControl>().enabled = true;
        }
        else if (Input.GetKeyDown(KeyCode.Alpha6))  // Shoulders
        {
            target1.GetComponent<FullControl>().ResetTarget();
            target1.GetComponent<FullControl>().enabled = false;
            target2.GetComponent<FullControl>().ResetTarget();
            target2.GetComponent<FullControl>().enabled = false;

            // Turn off the respective scripts
            rUpper.enabled = Upper.enabled = false;
            rLower.enabled = Lower.enabled = false;
            rHand.enabled = Hand.enabled = false;

            target1.GetComponent<FullControl>().enabled = false;
            target2.GetComponent<FullControl>().enabled = false;

            rShoulderScript.enabled = ShoulderScript.enabled = true;
        }
    }
}
