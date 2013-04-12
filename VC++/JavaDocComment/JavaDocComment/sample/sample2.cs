#if false

using System;
using System.Collections;
using DoxyComment;
using EnvDTE;
using System.ComponentModel;
using Microsoft.VisualStudio.VCCodeModel;

namespace JavaDocComment
{
   [CommentProviderFriendlyName("JavaDocComment")]
   public class JavaDocComment : DoxyComment.ICommentProvider
   {
       [CommentProviderProperty]
       private string firstLineTag = "/**";
       [CommentProviderProperty]
       private string normalLineTag = " * ";
       [CommentProviderProperty]
       private string lastLineTag = " */";
       [CommentProviderProperty]
       private string commandPrefix = "@";
       [CommentProviderProperty]
       private string author ="";

       public JavaDocComment()
       {
       }

       [Category("�R�����g�u���b�N�T��"),
       Description("�R�����g�u���b�N�̐擪�s�̐ړ����ł�.")]
       public string FirstLineTag
       {
           get
           {
               return firstLineTag;
           }
           set
           {
               firstLineTag = value;
           }
       }

       [Category("�R�����g�u���b�N�T��"),
      Description("�R�����g�u���b�N�̍s�̐ړ����ł�.")]
       public string NormalLineTag
       {
           get
           {
               return normalLineTag;
           }
           set
           {
               normalLineTag = value;
           }
       }

       [Category("�R�����g�u���b�N�T��"),
      Description("�R�����g�u���b�N�̍ŏI�s�̐ړ����ł�.")]
       public string LastLineTag
       {
           get
           {
               return lastLineTag;
           }
           set
           {
               lastLineTag = value;
           }
       }
       [Category("�R�}���h�ړ���"),
       Description("�R�}���h�̐ړ����ł��B\\��@���w�肵�܂�.")]
       public string CommandPrefix
       {
           get
           {
               return commandPrefix;
           }
           set
           {
               commandPrefix = value;
           }
       }
       [Category("�����"),
       Description("����҂��w�肵�܂�.")]
       public string Author
       {
           get
           {
               return author;
           }
           set
           {
               author = value;
           }
       }
#region ICommentProvider implementation

       private ArrayList CreateCommentHeader(VCCodeElement codeElem)
       {
           ArrayList rv = new ArrayList();

           if (FirstLineTag.Length > 0)
           {
               rv.Add(FirstLineTag);
           }

           rv.Add(NormalLineTag + "������" + codeElem.Name + "�̗v����L��.");
           rv.Add(NormalLineTag + "������" + codeElem.Name + "�̏ڍׂ��L��.");
           return rv;
       }

       private void AppendCommentFooter(VCCodeElement codeElem, ArrayList buffer)
       {
           buffer.Add(NormalLineTag + CommandPrefix +"remarks ������" + codeElem.Name + "�̔��l���L��.");

           // Does the comment provider require a last line tag?
           if (LastLineTag.Length > 0)
           {
               buffer.Add(LastLineTag);
           }
       }

       public string[] CreateFileComment(Document doc)
       {
           ArrayList rv = new ArrayList();
           DateTime now = DateTime.Now;

           // Begin tag?
           if (FirstLineTag.Length > 0)
           {
               rv.Add(FirstLineTag);
           }

           rv.Add(NormalLineTag + "������" + doc.Name + "�̊T�v���L��.");
           rv.Add(NormalLineTag + CommandPrefix + "file    " + doc.Name);
           rv.Add(NormalLineTag + CommandPrefix + "author  " + Author);
           rv.Add(NormalLineTag + CommandPrefix + "date    " + now.ToString("yyyy/MM/dd"));
           rv.Add(NormalLineTag + CommandPrefix + "version ");

           // End tag?
           if (LastLineTag.Length > 0)
           {
               rv.Add(LastLineTag);
           }

           return (string[])rv.ToArray(typeof(string));
       }

       public string[] CreateTypeDefComment(VCCodeTypedef codeElem)
       {
           ArrayList rv;

           rv = CreateCommentHeader((VCCodeElement)codeElem);
           AppendCommentFooter((VCCodeElement)codeElem, rv);

           return (string[])rv.ToArray(typeof(string));
       }

       public string[] CreateUnionComment(VCCodeUnion codeElem)
       {
           ArrayList rv;

           rv = CreateCommentHeader((VCCodeElement)codeElem);
           AppendCommentFooter((VCCodeElement)codeElem, rv);

           return (string[])rv.ToArray(typeof(string));
       }

       public string[] CreateMacroComment(VCCodeMacro codeElem)
       {
           ArrayList rv;

           rv = CreateCommentHeader((VCCodeElement)codeElem);
           if ((codeElem.Parameters.Count > 0))
           {
               foreach (VCCodeParameter curParam in codeElem.Parameters)
               {
                   rv.Add(NormalLineTag + CommandPrefix +"param   " + curParam.Name
                       + " �p�����[�^" + curParam.Name + "�̐������L��.");
               }
           }
           AppendCommentFooter((VCCodeElement)codeElem, rv);

           return (string[])rv.ToArray(typeof(string));
       }

       public string[] CreateStructComment(VCCodeStruct codeElem)
       {
           ArrayList rv;

           rv = CreateCommentHeader((VCCodeElement)codeElem);
           AppendCommentFooter((VCCodeElement)codeElem, rv);

           return (string[])rv.ToArray(typeof(string));
       }

       public string[] CreateNamespaceComment(VCCodeNamespace codeElem)
       {
           ArrayList rv;

           rv = CreateCommentHeader((VCCodeElement)codeElem);
           AppendCommentFooter((VCCodeElement)codeElem, rv);

           return (string[])rv.ToArray(typeof(string));
       }

       public string[] CreateFunctionComment(VCCodeFunction codeElem)
       {
           ArrayList rv;

           rv = CreateCommentHeader((VCCodeElement)codeElem);

           // Create /param sections for each parameters in the function
           if (codeElem.Parameters.Count > 0)
           {
               foreach (VCCodeParameter curParam in codeElem.Parameters)
               {

                   rv.Add(NormalLineTag + CommandPrefix +"param   " + curParam.Name
                       + " �p�����[�^" + curParam.Name + "�̐������L��.");
               }
           }
           rv.Add(NormalLineTag + CommandPrefix + "see     ");
           // Create /returns section
           if ((codeElem.TypeString.Length > 0) &
               (codeElem.TypeString.ToLower() != "void"))
           {

               rv.Add(NormalLineTag + CommandPrefix +"return  "
                   + "�����ɖ߂�l�̐������L��.");
           }

           // Create /throws section
           rv.Add(NormalLineTag + CommandPrefix +"throws <exception class> ���̗�O�𓊂��邽�߂̊�̐������L��.");

           AppendCommentFooter((VCCodeElement)codeElem, rv);

           return (string[])rv.ToArray(typeof(string));
       }

       public string[] CreateEnumValueComment(VCCodeVariable codeElem)
       {
           ArrayList rv = new ArrayList();

           if (FirstLineTag.Length > 0)
           {
               rv.Add(FirstLineTag);
           }

           rv.Add(NormalLineTag + CommandPrefix +"brief   ������ " + codeElem.Name + " �̗v����L��.");

           // End tag required?
           if (LastLineTag.Length > 0)
           {
               rv.Add(LastLineTag);
           }

           return (string[])rv.ToArray(typeof(string));
       }

       public string[] CreateEnumComment(VCCodeEnum codeElem)
       {
           ArrayList rv;

           rv = CreateCommentHeader((VCCodeElement)codeElem);
           AppendCommentFooter((VCCodeElement)codeElem, rv);

           return (string[])rv.ToArray(typeof(string));
       }

       public string[] CreateVariableComment(VCCodeVariable codeElem)
       {
           ArrayList rv;

           rv = CreateCommentHeader((VCCodeElement)codeElem);
           AppendCommentFooter((VCCodeElement)codeElem, rv);

           return (string[])rv.ToArray(typeof(string));
       }

       public string[] CreateClassComment(VCCodeClass codeElem)
       {
           ArrayList rv;

           // Header
           rv = CreateCommentHeader((VCCodeElement)codeElem);

           // Template parameters?
           if ((codeElem.IsTemplate))
           {
               foreach (VCCodeParameter curTemplateParam in codeElem.Templatizations)
               {
                   string typeStr;
                   if ((curTemplateParam.Name.Length != 0))
                   {
                       typeStr = curTemplateParam.Name;
                   }
                   else
                   {
                       int typeIdx;

                       typeIdx = curTemplateParam.TypeString.LastIndexOf(" ");
                       typeStr = curTemplateParam.TypeString.Substring(typeIdx + 1);
                   }

                   rv.Add(NormalLineTag + CommandPrefix +"param   " + typeStr + " �p�����[�^" + typeStr + "�̐������L��.");
               }
           }

           AppendCommentFooter((VCCodeElement)codeElem, rv);

           return (string[])rv.ToArray(typeof(string));
       }

#endregion
   }
}

#endif
