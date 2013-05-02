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
        private string author = "";

        public JavaDocComment()
        {
        }

        [Category("コメントブロック概観"),
        Description("コメントブロックの先頭行の接頭辞です.")]
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

        [Category("コメントブロック概観"),
       Description("コメントブロックの行の接頭辞です.")]
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

        [Category("コメントブロック概観"),
       Description("コメントブロックの最終行の接頭辞です.")]
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
        [Category("コマンド接頭辞"),
        Description("コマンドの接頭辞です。\\や@を指定します.")]
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
        [Category("制作者"),
        Description("制作者を指定します.")]
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

            // DEL 20130502 20:49:38 sunada@ipl Start -->
            //rv.Add(NormalLineTag + "ここに" + codeElem.Name + "の要約を記載.");
            //rv.Add(NormalLineTag + "ここに" + codeElem.Name + "の詳細を記載.");
            // DEL 20130502 20:49:38 sunada@ipl  End  <--
            return rv;
        }

        private void AppendCommentFooter(VCCodeElement codeElem, ArrayList buffer)
        {
            // DEL 20130502 20:55:49 sunada@ipl Start -->
            //buffer.Add(NormalLineTag + CommandPrefix + "brief ここに" + codeElem.Name + "の要約を記載.");
            //buffer.Add(NormalLineTag + CommandPrefix + "note  ここに" + codeElem.Name + "の詳細を記載.");
            // DEL 20130502 20:55:49 sunada@ipl  End  <--

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

            rv.Add(NormalLineTag + "ここに" + doc.Name + "の概要を記載.");
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
            // DEL 20130502 20:35:29 sunada@ipl Start -->
            //if ((codeElem.Parameters.Count > 0))
            //{
            //    foreach (VCCodeParameter curParam in codeElem.Parameters)
            //    {
            //        rv.Add(NormalLineTag + CommandPrefix + "param   " + curParam.Name
            //            + " パラメータ" + curParam.Name + "の説明を記載.");
            //    }
            //}
            // DEL 20130502 20:35:29 sunada@ipl  End  <--
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
            rv.Add(NormalLineTag + "ここに" + codeElem.Name + "の概要を記載.");
            // DEL 20130502 20:35:53 sunada@ipl Start -->
            //if (codeElem.Parameters.Count > 0)
            //{
            //    foreach (VCCodeParameter curParam in codeElem.Parameters)
            //    {

            //        rv.Add(NormalLineTag + CommandPrefix + "param   " + curParam.Name
            //            + " パラメータ" + curParam.Name + "の説明を記載.");
            //    }
            //}
            //rv.Add(NormalLineTag + CommandPrefix + "see     ");
            // DEL 20130502 20:35:53 sunada@ipl  End  <--
            // Create /returns section
            if ((codeElem.TypeString.Length > 0) &
                (codeElem.TypeString.ToLower() != "void"))
            {
                rv.Add(NormalLineTag + CommandPrefix + "return  " + "ここに戻り値の説明を記載.");
                rv.Add(NormalLineTag + CommandPrefix + "retval  " + "ここに戻り値の説明を記載.");
                rv.Add(NormalLineTag + CommandPrefix + "note    " + "ここに" + codeElem.Name + "の詳細を記載.");
            }

            // Create /throws section
            // DEL 20130502 20:41:22 sunada@ipl Start -->
            //rv.Add(NormalLineTag + CommandPrefix + "throws <exception class> この例外を投げるための基準の説明を記載.");
            // DEL 20130502 20:41:22 sunada@ipl  End  <--

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

            rv.Add(NormalLineTag + CommandPrefix + "brief ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(NormalLineTag + CommandPrefix + "note  ここに" + codeElem.Name + "の詳細を記載.");

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

            // ADD 20130502 20:59:14 sunada@ipl Start -->
            rv.Add(NormalLineTag + CommandPrefix + "brief ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(NormalLineTag + CommandPrefix + "note  ここに" + codeElem.Name + "の詳細を記載.");
            // ADD 20130502 20:59:14 sunada@ipl  End  <--

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

                    rv.Add(NormalLineTag + CommandPrefix + "param   " + typeStr + " パラメータ" + typeStr + "の説明を記載.");
                }
            }

            AppendCommentFooter((VCCodeElement)codeElem, rv);

            return (string[])rv.ToArray(typeof(string));
        }

        #endregion
    }
}