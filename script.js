function compressText() {
    const text = document.getElementById("inputText").value;
    if (!text) return alert("Enter some text!");

    // Step 1: Frequency count
    let freq = {};
    for (let ch of text) {
        freq[ch] = (freq[ch] || 0) + 1;
    }

    // Step 2: Build nodes
    let nodes = Object.keys(freq).map(ch => ({
        char: ch,
        freq: freq[ch],
        left: null,
        right: null
    }));

    // Step 3: Build Huffman tree
    while (nodes.length > 1) {
        nodes.sort((a, b) => a.freq - b.freq);
        let left = nodes.shift();
        let right = nodes.shift();
        nodes.push({
            char: null,
            freq: left.freq + right.freq,
            left,
            right
        });
    }

    let tree = nodes[0];

    // Step 4: Generate codes
    let codes = {};
    function generateCodes(node, code) {
        if (!node) return;
        if (node.char !== null) {
            codes[node.char] = code;
        }
        generateCodes(node.left, code + "0");
        generateCodes(node.right, code + "1");
    }
    generateCodes(tree, "");

    // Step 5: Encode text
    let compressed = "";
    for (let ch of text) {
        compressed += codes[ch];
    }

    // Sizes
    let originalBits = text.length * 8;
    let compressedBits = compressed.length;

    document.getElementById("originalSize").innerText =
        `Original Size: ${originalBits} bits`;

    document.getElementById("compressedSize").innerText =
        `Compressed Size (logical): ${compressedBits} bits`;

    document.getElementById("outputText").value = compressed;
}
