using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShoulderControl : MonoBehaviour
{
    public float rotateSpeed = 75f;
    public bool right = true;
    private Vector3 e, q, w, s;

    void Start()
    {
        e = new Vector3(0, 0, 1);
        q = new Vector3(0, 0, -1);
        w = new Vector3(0, -1, 0);
        s = new Vector3(0, 1, 0);

        if (!right)
        {
            e = new Vector3(0, 0, -1);
            q = new Vector3(0, 0, 1);
            w = new Vector3(0, -1, 0);
            s = new Vector3(0, 1, 0);
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.E))
            this.transform.Rotate(e * rotateSpeed * Time.deltaTime);
        if (Input.GetKey(KeyCode.Q))
            this.transform.Rotate(q * rotateSpeed * Time.deltaTime);
        if (Input.GetKey(KeyCode.W))
            this.transform.Rotate(w * rotateSpeed * Time.deltaTime);
        if (Input.GetKey(KeyCode.S))
            this.transform.Rotate(s * rotateSpeed * Time.deltaTime);
    }
}
