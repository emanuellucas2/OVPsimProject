function toggleFolder(id, imageNode) {
  var imgBase      = "inc/_images/";
  var closedImg    = imgBase + "folderclosed.png";
  var openImg      = imgBase + "folderopen.png";
  var mnodeImg     = imgBase + "mnode.png";
  var pnodeImg     = imgBase + "pnode.png";
  var mlastNodeImg = imgBase + "mlastnode.png";
  var plastNodeImg = imgBase + "plastnode.png";

  var folder = parent.treefrm.document.getElementById(id);
  var l = imageNode.src.length;
  if (imageNode.src.substring(l-closedImg.length,l)==closedImg || imageNode.src.substring(l-openImg.length,l)==openImg) {
    imageNode = imageNode.previousSibling;
    l = imageNode.src.length;
  }
  if (folder == null) {
  } else if (folder.style.display == "block") {
    if (imageNode != null) {
      imageNode.nextSibling.src = closedImg;
      if (imageNode.src.substring(l-mnodeImg.length,l) == mnodeImg) {
        imageNode.src = pnodeImg;
      } else if (imageNode.src.substring(l-mlastNodeImg.length,l) == mlastNodeImg) {
        imageNode.src = plastNodeImg;
      }
    }
    folder.style.display = "none";
  } else {
    if (imageNode != null) {
      imageNode.nextSibling.src = openImg;
      if (imageNode.src.substring(l-pnodeImg.length,l) == pnodeImg) {
        imageNode.src = mnodeImg;
      } else if (imageNode.src.substring(l-plastNodeImg.length,l) == plastNodeImg) {
        imageNode.src = mlastNodeImg;
      }
    }
    folder.style.display = "block";
  }
}
