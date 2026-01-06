using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// Vector3(x, y, z)
// =======================================
// Vector3.up      = Vector3( 0,  1,  0) 
// Vector3.down    = Vector3( 0, -1,  0)
// Vector3.forward = Vector3( 0,  0,  1)
// Vector3.back    = Vector3( 0,  0, -1)
// Vector3.left    = Vector3(-1,  0,  0)
// Vector3.right   = Vector3( 1,  0,  0)

public class RotateThatThang : MonoBehaviour
{
    public GameObject thingToRotate;
    public float rotateSpeed = 75f;
    public bool rightControl = false;   // for multiplier
    public bool isUpper = false;        // for Vector3's
    public bool isLower = false;
    public bool leftOnly = false;

    private float multiplier = 1;
    private float multi = 1;
    private Vector3 w, s, a, d, e, q;

    void Start()
    {
        Init();
    }

    public void Init()
    {
        if (rightControl)
            multiplier = -1;
        else
            multiplier = 1;

        if (leftOnly)
            multi = -1;
        else
            multi = 1;

        if (isUpper)
        {
            w = (Vector3.up * multiplier) + Vector3.left;           // 2) Extension
            s = (Vector3.down * multiplier) + Vector3.right;        // 2) Flexion
            a = Vector3.forward * multiplier * multi;               // 1) Adduction
            d = Vector3.back * multiplier * multi;                  // 1) Adduction
            // 3) External rotation
            e = new Vector3(-1, -1, 0) * multi;
            if (rightControl)
                e = Vector3.left + Vector3.up;
            // 3) Internal rotation
            q = new Vector3(1, 1, 0) * multi;
            if (rightControl)
                q = Vector3.right + Vector3.down;
        }
        else if (isLower)
        {
            // 4) Elbow flexion ---> Behaving weird, good for now
            w = new Vector3(0, 0.8f, 0.76f);
            if (rightControl)
                w = new Vector3(0, -0.8f, -0.76f);
            // 4) Elbow extension ---> Behaving weird, good for now
            s = new Vector3(0, -0.8f, -0.76f);
            if (rightControl)
                s = new Vector3(0, 0.8f, 0.76f);
            a = new Vector3(0, 0, 0);
            d = new Vector3(0, 0, 0);
            e = new Vector3(0, 0, 0);
            q = new Vector3(0, 0, 0);
        }
        else
        {
            w = new Vector3(-1, 0, 0);      // Wrist Extension
            s = new Vector3(1, 0, 0);       // Wrist Flexion
            // 7) Radial Deviation
            a = new Vector3(0, 1, 0);
            if (rightControl || leftOnly)
                a = new Vector3(0, -1, 0);
            // 7) Ulnar Deviation
            d = new Vector3(0, -1, 0);
            if (rightControl || leftOnly)
                d = new Vector3(0, 1, 0);
            // 5) Forarm supination
            e = new Vector3(-1.0f, -1.0f, 1.0f) * multi;
            if (rightControl)
                e = new Vector3(-1.0f, 1.0f, -1.0f);
            // 5) Forarm pronation
            q = new Vector3(1.0f, 1.0f, -1.0f) * multi;
            if (rightControl)
                q = new Vector3(1.0f, -1.0f, 1.0f);
        }
    }

    void Update()
    {
        if (Input.GetKey(KeyCode.W))
            thingToRotate.transform.Rotate(w * rotateSpeed * Time.deltaTime);
        if (Input.GetKey(KeyCode.S))
            thingToRotate.transform.Rotate(s * rotateSpeed * Time.deltaTime);
        if (Input.GetKey(KeyCode.A))
            thingToRotate.transform.Rotate(a * rotateSpeed * Time.deltaTime);
        if (Input.GetKey(KeyCode.D))
            thingToRotate.transform.Rotate(d * rotateSpeed * Time.deltaTime);
        if (Input.GetKey(KeyCode.E))
            thingToRotate.transform.Rotate(e * rotateSpeed * Time.deltaTime);
        if (Input.GetKey(KeyCode.Q))
            thingToRotate.transform.Rotate(q * rotateSpeed * Time.deltaTime);
    }
}
